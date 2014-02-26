#include "telegram.h"

#include <QDebug>

#include "telegram_p.h"

#include "chatsmodel.h"

Telegram::Telegram(QObject *parent)
    : QObject(parent)
    , d_ptr(new TelegramPrivate(this))
{
}

Telegram::Status Telegram::status() const
{
    Q_D(const Telegram);
    return d->status;
}

ChatsModel* Telegram::chatsModel() const
{
    Q_D(const Telegram);
    return d->chatsModel;
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

