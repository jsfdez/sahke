#ifndef TELEGRAMTHREAD_H
#define TELEGRAMTHREAD_H

#include <QThread>

class TelegramThreadPrivate;

class TelegramThread : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(TelegramThread)
    Q_PROPERTY(State currentState READ currentState NOTIFY stateChanged)

public:
    enum class State
    {
        Idle,
        Working
    };

    explicit TelegramThread(QObject *parent = 0);
    ~TelegramThread();

    int lastResult() const;

    State currentState() const;

    Q_INVOKABLE void initialize();
    Q_INVOKABLE void registerPhone(const QString& phoneNumber);

signals:
    void stateChanged(State value);

//protected:
//    virtual void run();

private:
    TelegramThreadPrivate* d_ptr;
};

Q_DECLARE_METATYPE(TelegramThread::State)

#endif // TELEGRAMTHREAD_H
