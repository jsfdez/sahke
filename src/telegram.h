#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <QObject>

class TelegramPrivate;

class Telegram : public QObject
{
    Q_OBJECT
    Q_ENUMS(Status)
    Q_DECLARE_PRIVATE(Telegram)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)

public:
    enum Status
    {
        Connecting,
        Connected
    };

    explicit Telegram(QObject *parent = 0);
    Status status() const;

public slots:
    void start();
    void registerPhoneNumber(const QString& phoneNumber);
    void completeRegistration(const QString& code, const QString& firstName,
                              const QString& lastName);

signals:
    void phoneNumberRequested();
    void codeResquested();
    void registrationRequested();
    void statusChanged();

private:
    TelegramPrivate* d_ptr;
};

#endif // TELEGRAM_H
