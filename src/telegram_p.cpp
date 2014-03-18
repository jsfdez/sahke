#include "telegram_p.h"

#include <QDebug>
#include <QEventLoop>
#include <future>
#include <string>

#include "chatsmodel.h"
#include "tools.h"
#include "chat.h"

extern "C"
{
void do_insert_header (void);
#include "queries.h"
}

#include "mtproto-common.h"

TelegramPrivate::TelegramPrivate(Telegram* parent)
    : QThread(parent)
    , q_ptr(parent)
    , status(Telegram::Status::Connecting)
    , chatsModel(new PeersModel(this))
{
    pConfig.ctx = this;
    pConfig.verbosity = 0;
    pConfig.pfn_ask_username = (fn_ask_username_callback)
            &TelegramPrivate::onUsernameCallback;
    pConfig.pfn_ask_code = (fn_ask_code_callback)
            &TelegramPrivate::onCheckCodeCallback;
    pConfig.pfn_ask_code_register = (fn_ask_code_register_callback)
            &TelegramPrivate::onRegisterCallback;
    pConfig.pfn_connected = (fn_connected_callback)
            &TelegramPrivate::onConnected;

    pConfig.get_chats_callback.object = chatsModel;
    pConfig.get_chats_callback.function = &TelegramPrivate::onNewChat;
}

void TelegramPrivate::run()
{
    qDebug() << "Calling tg-main";
    initialize_lib_tg(&pConfig);
}

void TelegramPrivate::onUsernameCallback(void *context, char **username)
{
    qDebug() << "Recibing username callback";
    TelegramPrivate* q = static_cast<TelegramPrivate*>(context);
    std::promise<QString> promise;
    std::future<QString> future = promise.get_future();
    connect(q, &TelegramPrivate::phoneNumberSet, [&promise](
            const QString& phoneNumber)
    {
        promise.set_value(phoneNumber);
    });
    emit q->q_ptr->phoneNumberRequested();

    *username = tstrdup(future.get().toLatin1().data());
}

void TelegramPrivate::onCheckCodeCallback(void *context, char **code)
{
    qDebug() << "SMS verification";
    TelegramPrivate* q = static_cast<TelegramPrivate*>(context);
    std::promise<QString> promise;
    std::future<QString> future = promise.get_future();
    connect(q, &TelegramPrivate::userDataSet, [&promise](const QString& code,
            const QString&, const QString&)
    {
        promise.set_value(code);
    });
    emit q->q_ptr->codeResquested();

    *code = tstrdup(future.get().toLatin1().data());
}

void TelegramPrivate::onRegisterCallback(void *context, char **code,
                                         char **first_name, char **last_name)
{
    TelegramPrivate* q = static_cast<TelegramPrivate*>(context);
    std::promise<std::tuple<QString,QString,QString>> promise;
    std::future<std::tuple<QString,QString,QString>> future = promise
            .get_future();
    connect(q, &TelegramPrivate::userDataSet, [&promise](const QString& code,
            const QString& firstName, const QString& lastName)
    {
        promise.set_value(std::make_tuple(code, firstName, lastName));
    });
    emit q->q_ptr->registrationRequested();
    QString _code, firstName, lastName;

    future.wait();
    std::tie(_code, firstName, lastName) = future.get();
    *code = tstrdup(_code.toLatin1().data());
    *first_name = tstrdup(firstName.toLatin1().data());
    *last_name = tstrdup(lastName.toLatin1().data());
}

void TelegramPrivate::onConnected(void *context)
{
    TelegramPrivate* q = static_cast<TelegramPrivate*>(context);
    q->setStatus(Telegram::Status::Connected);
}

void TelegramPrivate::onNewChat(void *context, peer_id_t id, peer_t *U)
{
    TelegramPrivate* q = static_cast<TelegramPrivate*>(context);
    q->metaObject()->invokeMethod(q->chatsModel, "addNewChat",
                                  Q_ARG(peer_id_t, id),
                                  Q_ARG(peer_t*, U));
}

void TelegramPrivate::onChatInformation(void *context, chat *C)
{
    TelegramPrivate* q = static_cast<TelegramPrivate*>(context);
    q->metaObject()->invokeMethod(q, QT_STRINGIFY(chatInformationReceived),
                                  Q_ARG(chat*, C));
}

void TelegramPrivate::chatInformationReceived(chat *C)
{
    qDebug() << __FUNCTION__ << C;
}

void TelegramPrivate::setStatus(Telegram::Status value)
{
    Q_Q(Telegram);
    if (status != value)
    {
        status = value;
        emit q->statusChanged();
    }
}

void TelegramPrivate::doGetDifference()
{
    QueryMethods queryMethods(this);
    clear_packet();
    do_insert_header();
    out_int(CODE_updates_get_state);
    send_query(DC_working, packet_ptr - packet_buffer, packet_buffer,
                &queryMethods, 0);
}
