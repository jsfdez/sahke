#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <QObject>

class TelegramPrivate;

class Telegram : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Telegram)

public:
    explicit Telegram(QObject *parent = 0);

public slots:
    void start();
    void registerPhoneNumber(const QString& phoneNumber);
    void completeRegistration(const QString& code, const QString& firstName,
                              const QString& lastName);

signals:
    void phoneNumberRequested();
    void codeResquested();
    void registrationRequested();

private:
    TelegramPrivate* d_ptr;
};

#endif // TELEGRAM_H
