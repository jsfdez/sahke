#include "telegram.h"

#include <QDebug>
#include <QMetaEnum>

#include "telegramthread.h"

extern int binlog_enabled;
extern int verbosity;

struct TelegramPrivate : QObject
{
    Q_DECLARE_PUBLIC(Telegram)

    typedef Telegram::State State;

    TelegramPrivate(Telegram* parent)
        : QObject(parent)
        , q_ptr(parent)
        , state(State::Idle)
        , registered(false)
    {
        connect(&telegramThread, &TelegramThread::stateChanged, this,
                &TelegramPrivate::threadStateChanged);

        telegramThread.moveToThread(&thread);
        thread.start();
    }

    Telegram* q_ptr;
    TelegramThread telegramThread;
    QThread thread;
    State state;
    bool registered;

    void setState(State value);
    void setRegistered(bool value);
    void threadStateChanged(TelegramThread::State state);
};

Telegram::Telegram(QObject *parent)
    : QObject(parent)
    , d_ptr(new TelegramPrivate(this))
{
    connect(this, &Telegram::stateChanged, [](State state)
    {
        qDebug() << "State changed to:" << state;
    });
}

Telegram::State Telegram::state() const
{
    Q_D(const Telegram);
    return d->state;
}

bool Telegram::isRegistered()
{
    Q_D(const Telegram);
    return d->registered;
}

bool Telegram::isBinaryModeEnabled() const
{
    return binlog_enabled != 0;
}

int Telegram::verbosityLevel() const
{
    return verbosity;
}

void Telegram::start()
{
    Q_D(Telegram);

    d->setState(State::Initializing);
    metaObject()->invokeMethod(&d->telegramThread, "initialize");
}

void Telegram::authorizePhone(const QString &phoneNumber)
{
    Q_D(Telegram);

    qDebug() << "Registering phone " << phoneNumber << QThread::currentThread();
    d->setState(State::CheckingPhone);
    metaObject()->invokeMethod(&d->telegramThread, "registerPhone",
                               Q_ARG(QString, phoneNumber));
}

void Telegram::setBinaryModeEnabled(bool value)
{
    if(isBinaryModeEnabled() != value)
    {
        binlog_enabled = value ? 1 : 0;
        emit binaryModeEnabledChanged();
    }
}

void Telegram::setVerbosityLevel(int value)
{
    if(verbosity != value)
    {
        verbosity = value;
        emit verbosityLevelChanged();
    }
}


void TelegramPrivate::setState(TelegramPrivate::State value)
{
    Q_Q(Telegram);
    if(state != value)
    {
        state = value;
        emit q->stateChanged(state);
    }
}

void TelegramPrivate::setRegistered(bool value)
{
    Q_Q(Telegram);
    if(registered != value)
    {
        registered = value;
        emit q->registeredChanged(value);
    }
}

void TelegramPrivate::threadStateChanged(TelegramThread::State s)
{
    Q_Q(Telegram);
    switch (state) {
    case Telegram::State::Idle:
        break;
    case Telegram::State::Initializing:
        if(s == TelegramThread::State::Idle)
        {
            setState(Telegram::State::Idle);
            emit q->initialized();
        }
        break;
    case Telegram::State::CheckingPhone:
        if(s == TelegramThread::State::Idle)
        {
            setState(Telegram::State::Idle);
            qDebug()<< "Result?" << telegramThread.lastResult();
            setRegistered(telegramThread.lastResult() >= 0);
            emit q->authorizedPhone();
        }
        break;
    }
}

QDebug operator<<(QDebug dbg, const Telegram::State &c)
{
    typedef Telegram::State State;
    QMetaObject mo = Telegram::staticMetaObject;
    int index = mo.indexOfEnumerator(QT_STRINGIFY(State));
    QMetaEnum e = mo.enumerator(index);
    QString str(e.key(static_cast<int>(c)));
    dbg.nospace() << str;
    return dbg.space();
}
