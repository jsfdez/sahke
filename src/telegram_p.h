#ifndef TELEGRAM_P_H
#define TELEGRAM_P_H

#include <QThread>
#include <memory>

#include "telegram.h"

extern "C"
{
#include "libtg.h"
}

class TelegramPrivate : public QThread
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(Telegram)

public:
    TelegramPrivate(Telegram* parent);

signals:
    void phoneNumberSet(const QString& phoneNumber);
    void userDataSet(const QString& code, const QString& firstName,
                     const QString& lastName);

protected:
    virtual void run();

private:
    static void onUsernameCallback(void* context, char** username);
    static void onCheckCodeCallback(void* context, char** code);
    static void onRegisterCallback(void* context, char** code, char** firstName,
                                   char** lastName);
    static void onConnected(void* context);
    void setStatus(Telegram::Status value);

    Telegram* q_ptr;
    std::unique_ptr<configuration> pConfig;
    Telegram::Status status;
};

#endif // TELEGRAM_P_H
