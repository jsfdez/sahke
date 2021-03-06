#include "telegram.h"

#include <QDebug>

#include "telegram_p.h"

#include "chatsmodel.h"

Telegram::Telegram(QObject *parent)
    : QObject(parent)
    , d_ptr(new TelegramPrivate(this))
{
}

Telegram *Telegram::instance()
{
    static Telegram telegram;
    return &telegram;
}

Telegram::Status Telegram::status() const
{
    Q_D(const Telegram);
    return d->status;
}

PeersModel* Telegram::chatsModel() const
{
    Q_D(const Telegram);
    return d->chatsModel;
}

QList<ChatModel*> Telegram::peerList() const
{
    Q_D(const Telegram);
    return d->peerList;
}

void Telegram::start()
{
    Q_D(Telegram);
    d->start();
}

void Telegram::registerPhoneNumber(const QString &phoneNumber)
{
    Q_D(Telegram);
    emit d->phoneNumberSet(phoneNumber);
}

void Telegram::completeRegistration(const QString &code,
                                    const QString &firstName,
                                    const QString &lastName)
{
    Q_D(Telegram);
    emit d->userDataSet(code, firstName, lastName);
}

extern "C" void do_get_chat_info (peer_id_t id);

void Telegram::chatInfo(int chatType, int index)
{
    do_get_chat_info({chatType, index});
}
