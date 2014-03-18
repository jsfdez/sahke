#include "chat.h"
#include <QDebug>

extern "C" {
#include "libtg.h"
#include "queries.h"
#include "constants.h"
#include "mtproto-common.h"
int get_history_on_answer (struct query *q);
void out_peer_id (peer_id_t id);
}

ChatModel::ChatModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_type(-1)
    , m_id(-1)
    , m_peer(nullptr)
{
}

int ChatModel::rowCount(const QModelIndex&) const
{
    int count = 0;
    if (m_peer != nullptr)
    {
        struct message* message = m_peer->chat.last;
        while(message)
        {
            count++;
            message = message->next;
        }
    }
    return count;
}

QVariant ChatModel::data(const QModelIndex& index, int role) const
{
    Q_ASSERT(m_peer != nullptr);
    struct message* message = messageIndex(index.row());

    if (message != nullptr) switch(role)
    {
    case TextRole:
        if(message->service == 0)
        {
            Q_ASSERT(message->text && message->text_len > 0);
            return QString::fromUtf8(message->text, message->text_len);
        }
        return QString();
    case DateRole:
        return message->date;
    case FromRole:
    {
        QString name = m_names.value(message->from_id.id);
        if (name.isEmpty())
            name = "Me";
        return name;
    }
    case ActionRole:
        return message->service == 0 ? Action::Message
                                     : mapToAction(message->action.type);
    }
    return QVariant();
}

QHash<int, QByteArray> ChatModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(TextRole, "text");
    roles.insert(DateRole, "date");
    roles.insert(FromRole, "from");
    roles.insert(ActionRole, "action");
    return roles;
}

bool ChatModel::loadChat(int type, int id)
{
    peer_id_t peerId = {type, id};
    peer_t* peer = user_chat_get(peerId);
    if(peer != m_peer)
    {
        getChatHistory(peerId);
        beginResetModel();
        beginInsertRows(QModelIndex(), 0, rowCount());
        switch(type) {
        case PEER_USER:
            m_names.insert(peer->user.id.id, peer->user.print_name);
            break;
        case PEER_CHAT:
            for(int i = 0; i < peer->chat.user_list_size; i++)
            {
                m_names.insert(peer->chat.user_list[i].user_id,
                               QString::number(peer->chat.last->id));
            }
        }
        m_type = type;
        m_id = id;
        m_peer = peer;
        emit titleChanged();
        endResetModel();
    }
    return peer != nullptr;
}

void ChatModel::sendText(const QString &text)
{
    peer_id_t peerId = {m_type, m_id};
    do_send_message(peerId, text.toUtf8().data(), text.count());
}

QString ChatModel::title() const
{
    if(m_peer) switch(m_type)
    {
    case PEER_CHAT: return m_peer->chat.title;
    case PEER_USER: return m_peer->user.print_name;
    }
    return QString();
}

int ChatModel::onReceivedChatHistory(query *q)
{
    int retval;
    QueryMethods* queryMethods = (QueryMethods*)q->methods;
    retval = get_history_on_answer(q);
    queryMethods->context->metaObject()->invokeMethod(
                queryMethods->context, QT_STRINGIFY(updateChat));
    delete queryMethods;
    return retval;
}

void ChatModel::updateChat()
{
    Q_ASSERT(m_peer);
    beginResetModel();
    endResetModel();
}

void ChatModel::getChatHistory(peer_id_t id)
{
    QueryMethods* queryMethods = new QueryMethods(this);
    queryMethods->on_answer = &ChatModel::onReceivedChatHistory;
    queryMethods->peerId = id;

    clear_packet();
    out_int(CODE_messages_get_history);
    out_peer_id(id);
    out_int(0);
    out_int(0);
    out_int(10);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
    send_query(DC_working, packet_ptr - packet_buffer, packet_buffer,
               queryMethods, (void *)*(long *)&id);
#pragma GCC diagnostic pop
}

ChatModel::Action ChatModel::mapToAction(int code) const
{
    switch(code)
    {
    case CODE_message_action_chat_create: return Action::ChatCreated;
    case CODE_message_action_chat_edit_title: return Action::ChatChangeTitle;
    case CODE_message_action_chat_edit_photo: return Action::ChatChangePhoto;
    case CODE_message_action_chat_delete_photo: return Action::ChatDeletePhoto;
    case CODE_message_action_chat_add_user: return Action::ChatAddUser;
    case CODE_message_action_chat_delete_user: return Action::ChatDeleteUser;
    default: return Action::NotSupported;
    }
}

message* ChatModel::messageIndex(int row) const
{
    Q_ASSERT(m_peer != nullptr);
    struct message* message = nullptr;
    switch(m_type)
    {
    case PEER_USER: message = m_peer->user.last; break;
    case PEER_CHAT: message = m_peer->chat.last; break;
    }
    for (int i = 0; message != nullptr; i++, message = message->next)
        if (i == row)
            break;
    return message;
}
