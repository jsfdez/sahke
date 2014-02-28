#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <QObject>

class Peer;
class ChatsModel;
class TelegramPrivate;

class Telegram : public QObject
{
    Q_OBJECT
    Q_ENUMS(Status)
    Q_DECLARE_PRIVATE(Telegram)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(ChatsModel* chatsModel READ chatsModel NOTIFY chatsModelChanged)
    Q_PROPERTY(QList<Peer*> peerList READ peerList NOTIFY peerListChanged)

public:
    enum Status
    {
        Connecting,
        Connected
    };

    explicit Telegram(QObject *parent = 0);
    Status status() const;
    ChatsModel *chatsModel() const;
    QList<Peer*> peerList() const;

public slots:
    void start();
    void registerPhoneNumber(const QString& phoneNumber);
    void completeRegistration(const QString& code, const QString& firstName,
                              const QString& lastName);
    void chatInfo(int chatType, int index);

signals:
    void phoneNumberRequested();
    void codeResquested();
    void registrationRequested();
    void statusChanged();
    void chatsModelChanged();
    void peerListChanged();

private:
    TelegramPrivate* d_ptr;
};

#endif // TELEGRAM_H
