#ifndef TGLOOPTHREAD_H
#define TGLOOPTHREAD_H

#include <QThread>

#include <QFuture>

class Telegram;
class lua_State;

class TgLoopThread : public QThread
{
    Q_OBJECT
public:
    static TgLoopThread* instance();

signals:
    void phoneNumberRequested();
    void phoneNumberChanged();

protected:
    explicit TgLoopThread(QObject *parent = 0);
    virtual void run();

private:
    static int onBinlogReplayEnd(lua_State *L);
    static int onUsernameAsked(lua_State *L);
};

#endif // TGLOOPTHREAD_H
