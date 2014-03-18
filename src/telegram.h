#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <QObject>

class ChatModel;
class PeersModel;
class TelegramPrivate;

class Telegram : public QObject
{
    Q_OBJECT
    Q_ENUMS(Status)
    Q_DECLARE_PRIVATE(Telegram)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(PeersModel* chatsModel READ chatsModel NOTIFY chatsModelChanged)
    Q_PROPERTY(QList<ChatModel*> peerList READ peerList NOTIFY peerListChanged)

public:
    enum Status
    {
        Connecting,
        Connected
    };

    static Telegram* instance();

    Status status() const;
    PeersModel *chatsModel() const;
    QList<ChatModel*> peerList() const;

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
    explicit Telegram(QObject *parent = 0);
    TelegramPrivate* d_ptr;
};

#endif // TELEGRAM_H
