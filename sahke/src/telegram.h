#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <QObject>

class TelegramPrivate;

class Telegram : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Telegram)

    Q_ENUMS(State)
    Q_PROPERTY(bool binaryModeEnabled READ isBinaryModeEnabled
               WRITE setBinaryModeEnabled NOTIFY binaryModeEnabledChanged)
    Q_PROPERTY(int verbosityLevel READ verbosityLevel WRITE setVerbosityLevel
               NOTIFY verbosityLevelChanged)
    Q_PROPERTY(bool registered READ isRegistered NOTIFY registeredChanged)

public:
    enum class State
    {
        Idle,
        Initializing,
        CheckingPhone
    };

    explicit Telegram(QObject *parent = 0);

    State state() const;
    bool isRegistered();

    bool isBinaryModeEnabled() const;
    int verbosityLevel() const;

public slots:
    void start();
    void authorizePhone(const QString& phoneNumber);
    void setBinaryModeEnabled(bool value);
    void setVerbosityLevel(int value);

signals:
    void stateChanged(State state);
    void initialized();
    void authorizedPhone();
    void registeredChanged(bool value);
    void binaryModeEnabledChanged();
    void verbosityLevelChanged();

private:
    TelegramPrivate* d_ptr;
};

QDebug operator<<(QDebug dbg, const Telegram::State &c);

#endif // TELEGRAM_H
