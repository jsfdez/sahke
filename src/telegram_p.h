#ifndef TELEGRAM_P_H
#define TELEGRAM_P_H

#include <QThread>

#include "telegram.h"

class PeersModel;
class ChatModel;

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

    Telegram* q_ptr;
    libcfg pConfig;
    Telegram::Status status;
    PeersModel* chatsModel;
    QList<ChatModel*> peerList;

signals:
    void phoneNumberSet(const QString& phoneNumber);
    void userDataSet(const QString& code, const QString& firstName,
                     const QString& lastName);
    void newChatReceived(peer_id_t id, peer_t* U);

protected:
    virtual void run();

private:
    static void onUsernameCallback(void* context, char** username);
    static void onCheckCodeCallback(void* context, char** code);
    static void onRegisterCallback(void* context, char** code, char** firstName,
                                   char** lastName);
    static void onConnected(void* context);
    static void onNewChat(void* context, peer_id_t id, peer_t *U);
    static void onChatInformation(void* context, chat* C);
    void chatInformationReceived(struct chat* C);
    void setStatus(Telegram::Status value);
};

#endif // TELEGRAM_P_H
