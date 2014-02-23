#include "tgloopthread.h"

#include <QDebug>
#include <QGuiApplication>

#include <vector>
#include <string>

extern "C"
{
#include <lua.h>
int disabled_main (int argc, char **argv);
void lua_init ();
}

extern lua_State *luaState;

TgLoopThread *TgLoopThread::instance()
{
    static TgLoopThread singleton;
    return &singleton;
}

TgLoopThread::TgLoopThread(QObject *parent) :
    QThread(parent)
{
}

void TgLoopThread::run()
{
    qDebug() << "Thread started";
    std::vector<std::string> parameters;
    parameters.push_back("-B");
    parameters.push_back("-R");
    char** p = new char*[parameters.size()];

    for(size_t i = 0; i < parameters.size(); i++)
    {
        p[i] = (char*)parameters[i].c_str();
    }

    lua_init();
    lua_register(luaState, "on_binlog_replay_end", onBinlogReplayEnd);
    lua_register(luaState, "on_username_asked", onUsernameAsked);
    qDebug() << "Lua functions registered";

    qDebug() << "Calling tg-main";
    disabled_main(2, p);
    delete [] p;
}

int TgLoopThread::onBinlogReplayEnd(lua_State *L)
{
    Q_UNUSED(L);
    return 0;
}

int TgLoopThread::onUsernameAsked(lua_State *L)
{
    Q_UNUSED(L);
    QEventLoop eventLoop;
    emit instance()->phoneNumberRequested();

    connect(instance(), &TgLoopThread::phoneNumberChanged, &eventLoop,
            &QEventLoop::quit);
    eventLoop.exec();
    return 0;
}
