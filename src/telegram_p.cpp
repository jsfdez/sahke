#include "telegram_p.h"

#include <QDebug>
#include <QEventLoop>

TelegramPrivate::TelegramPrivate(Telegram* parent)
    : QThread(parent)
    , q_ptr(parent)
{
}

TelegramPrivate* TelegramPrivate::context(lua_State *L)
{
    lua_getglobal(L, CONTEXT);
    return reinterpret_cast<TelegramPrivate*>(lua_touserdata(L, 1));
}

void TelegramPrivate::run()
{
    qDebug() << "Thread started";

//    verbosity = 10;

    lua_init();
    lua_pushlightuserdata(luaState, this);
    lua_setglobal(luaState, CONTEXT);
    lua_register(luaState, "on_username_asked",
                 TelegramPrivate::onUsernameRequested);
    lua_register(luaState, "on_code_asked", TelegramPrivate::onCodeRequested);
    lua_register(luaState, "on_registration_asked",
                 TelegramPrivate::onRegistrationRequested);
    qDebug() << "Lua functions registered";

    qDebug() << "Calling tg-main";
    disabled_main(0, nullptr);
}

int TelegramPrivate::onUsernameRequested(lua_State *L)
{
    qDebug() << "username requested";
    TelegramPrivate* q = context(L);
    QEventLoop eventLoop;
    emit q->q_ptr->phoneNumberRequested();

    connect(q, &TelegramPrivate::phoneNumberSet, [&](const QString& phoneNumber)
    {
        qDebug() << "Signal received. canceling the eventloop";
        eventLoop.quit();
        lua_pushstring(L, phoneNumber.toLatin1().data());
    });
    qDebug() << "Event loop started";
    eventLoop.exec();
    qDebug() << "Event loop finished";
    return 1;
}

int TelegramPrivate::onCodeRequested(lua_State *L)
{
    qDebug() << "Authorization code requested";
    TelegramPrivate* q = context(L);
    QEventLoop eventLoop;
    emit q->q_ptr->codeResquested();

    connect(q, &TelegramPrivate::userDataSet, [&](const QString& code,
            const QString&, const QString&)
    {
        qDebug() << "Signal received. canceling the eventloop";
        eventLoop.quit();
        lua_pushstring(L, code.toLatin1().data());
    });
    eventLoop.exec();
    return 1;
}

int TelegramPrivate::onRegistrationRequested(lua_State *L)
{
    qDebug() << "Registration requested";
    TelegramPrivate* q = context(L);
    QEventLoop eventLoop;
    emit q->q_ptr->registrationRequested();

    connect(q, &TelegramPrivate::userDataSet, [&](const QString& code,
            const QString& firstName, const QString& lastName)
    {
        qDebug() << "Signal received. canceling the eventloop";
        eventLoop.quit();
        lua_pushstring(L, code.toLatin1().data());
        lua_pushstring(L, firstName.toLatin1().data());
        lua_pushstring(L, lastName.toLatin1().data());
    });
    eventLoop.exec();
    return 3;
}
