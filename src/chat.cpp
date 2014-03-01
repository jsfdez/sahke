#include "chat.h"

extern "C" {
#include "queries.h"
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
