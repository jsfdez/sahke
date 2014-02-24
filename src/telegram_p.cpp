#include "telegram_p.h"

#include <QDebug>
#include <QEventLoop>
#include <future>
#include <string>

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
    lua_register(luaState, "on_username_requested",
                 TelegramPrivate::onUsernameRequested);
    lua_register(luaState, "on_code_requested", TelegramPrivate::onCodeRequested);
    lua_register(luaState, "on_registration_requested",
                 TelegramPrivate::onRegistrationRequested);
    qDebug() << "Lua functions registered";

    qDebug() << "Calling tg-main";
    disabled_main(0, nullptr);
}

int TelegramPrivate::onUsernameRequested(lua_State *L)
{
    TelegramPrivate* q = context(L);
    std::promise<QString> promise;
    std::future<QString> future = promise.get_future();
    connect(q, &TelegramPrivate::phoneNumberSet, [&promise](
            const QString& phoneNumber)
    {
        promise.set_value(phoneNumber);
    });
    emit q->q_ptr->phoneNumberRequested();
    lua_pushstring(L, future.get().toLatin1().data());
//    std::packaged_task<QString(const QString&)> task(
//                [](const QString& phoneNumber)
//    {
//        return phoneNumber;
//    });
//    std::packaged_task<QString(const QString&)> qstringTask([](const QString& phoneNumber) -> QString { return phoneNumber; } );
//    std::future<QString> future = task.get_future();
//    connect(q, &TelegramPrivate::phoneNumberSet, qstringTask);
//    future.wait();
//    lua_pushstring(L, future.get().toLatin1().data());
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
