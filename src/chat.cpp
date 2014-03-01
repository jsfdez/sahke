#include "chat.h"
#include <QDebug>

extern "C" {
#include "libtg.h"
#include "queries.h"
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
    case MessageRole:
        qDebug() << "pedido mensaje:" << index.row();
        return message->text;
    case DateRole:
        return message->date;
    case FromRole:
    {
        QString name = m_names.value(message->from_id.id);
        if (name.isEmpty())
            name = "Me";
        return name;
    }
    }
    return QVariant();
}

QHash<int, QByteArray> ChatModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(MessageRole, "message");
    roles.insert(DateRole, "date");
    roles.insert(FromRole, "from");
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
        endResetModel();
    }
    return peer != nullptr;
}

void ChatModel::sendText(const QString &text)
{
    peer_id_t peerId = {m_type, m_id};
    do_send_message(peerId, text.toUtf8().data(), text.count());
}

int ChatModel::onReceivedChatHistory (query *q)
{
    int retval;
    QueryMethods* queryMethods = (QueryMethods*)q->methods;
    retval = get_history_on_answer(q);
    queryMethods->context->metaObject()->invokeMethod(
                queryMethods->context, QT_STRINGIFY(updateChat));

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
