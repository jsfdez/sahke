#include "telegramthread.h"

#include <QDebug>

#include <assert.h>

#include "tg/telegram.h"

#define __STRUCTURES_H__
extern "C" {
typedef struct { int type; int id; } peer_id_t;
#include "tg/net.h"
void on_start (void);
double get_double_time (void);
void logprintf (const char *format, ...);
void replay_log (void);
void write_binlog (void);
void read_auth_file (void);
char* get_auth_key_filename ();
void running_for_first_time (void);
void parse_config (void);
void update_prompt (void);
void dc_authorize (struct dc *DC);
void write_auth_file (void);
void do_help_get_config (void);
int mcs (void);
void net_loop (int flags, int (*is_end)(void));
void set_default_username (const char *s);
int do_auth_check_phone (const char *user);
}

extern long long pk_fingerprint;
extern int binlog_enabled;
extern int verbosity;
extern char* auth_file_name;
struct dc *DC_list[MAX_DC_ID + 1];
extern struct dc *DC_working;
extern int dc_working_num;
extern int auth_state;
extern int new_dc_num;
extern char *default_username;

struct TelegramThreadPrivate : QObject
{
    Q_DECLARE_PUBLIC(TelegramThread)

    TelegramThreadPrivate(TelegramThread* parent)
        : QObject(parent)
        , q_ptr(parent)
        , state(TelegramThread::State::Idle)
    {}

    TelegramThread* q_ptr;
    TelegramThread::State state;
    int lastResult;

    void setState(TelegramThread::State value)
    {
        Q_Q(TelegramThread);
        if (state != value)
        {
            state = value;
            emit q->stateChanged(state);
        }
    }

//    void initialize();
};

void TelegramThread::initialize()
{
    Q_D(TelegramThread);
    qDebug() << "Initialization started" << QThread::currentThread();
    d->setState(TelegramThread::State::Working);

    running_for_first_time();
    parse_config();

    on_start();
    if (binlog_enabled) {
        double t = get_double_time ();
        logprintf ("replay log start\n");
        replay_log ();
        logprintf ("replay log end in %lf seconds\n", get_double_time () - t);
        write_binlog ();
#ifdef USE_LUA
        lua_binlog_end ();
#endif
    } else {
        read_auth_file ();
    }
    update_prompt ();

    assert (DC_list[dc_working_num]);
    if (!DC_working || !DC_working->auth_key_id) {
        //  if (auth_state == 0) {
        DC_working = DC_list[dc_working_num];
        dc_authorize (DC_working);
        auth_state = 100;
        write_auth_file ();
    }

    if (verbosity) {
        logprintf ("Requesting info about DC...\n");
    }
    do_help_get_config ();
    net_loop (0, mcs);
    if (verbosity) {
        logprintf ("DC_info: %d new DC got\n", new_dc_num);
    }
    int i;
    for (i = 0; i <= MAX_DC_NUM; i++) if (DC_list[i] && !DC_list[i]->auth_key_id) {
        dc_authorize (DC_list[i]);
        write_auth_file ();
    }
    qDebug() << "Initialization completed";
    d->setState(TelegramThread::State::Idle);
}

TelegramThread::TelegramThread(QObject *parent)
    : QObject(parent)
    , d_ptr(new TelegramThreadPrivate(this))
{
    qDebug() << "Creating thread" << QThread::currentThread();
}

TelegramThread::~TelegramThread()
{
    delete d_ptr;
}

int TelegramThread::lastResult() const
{
    Q_D(const TelegramThread);
    return d->lastResult;
}

TelegramThread::State TelegramThread::currentState() const
{
    Q_D(const TelegramThread);
    return d->state;
}

void TelegramThread::registerPhone(const QString &phoneNumber)
{
    qDebug() << "Registering phone " << phoneNumber << QThread::currentThread();
    Q_D(TelegramThread);
    d->setState(TelegramThread::State::Working);

    set_default_username(phoneNumber.toLatin1().data());
    verbosity = 100;
    d->lastResult = do_auth_check_phone(default_username);
    Q_ASSERT(d->lastResult >= 0);
//    if (res > 0 && !register_mode) {
//      do_send_code (default_username);
//    }
//      qDebug() << "Code sent?";

    d->setState(TelegramThread::State::Idle);
}


//void TelegramThread::run()
//{
//    Q_D(TelegramThread);

//    d->initialize();
//    exec();
//}
