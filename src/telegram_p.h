#ifndef TELEGRAM_P_H
#define TELEGRAM_P_H

#include <QThread>

#include "telegram.h"

#define CONTEXT     "context"

extern "C"
{
#include <lua.h>
int disabled_main (int argc, char **argv);
void lua_init ();
}

extern lua_State *luaState;
extern char *default_username;
extern int verbosity;

class TelegramPrivate : public QThread
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(Telegram)

public:
    TelegramPrivate(Telegram* parent);

    static TelegramPrivate* context(lua_State* L);
    static int onUsernameRequested(lua_State* L);
    static int onCodeRequested(lua_State* L);
    static int onRegistrationRequested(lua_State* L);

signals:
    void phoneNumberSet(const QString& phoneNumber);
    void userDataSet(const QString& code, const QString& firstName,
                     const QString& lastName);

protected:
    virtual void run();

private:
    Telegram* q_ptr;
};

#endif // TELEGRAM_P_H
