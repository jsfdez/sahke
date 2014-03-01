#include "chatsmodel.h"

#include <QDebug>
#include <QEventLoop>
#include <QGuiApplication>

#include "chat.h"

extern "C" {
#include "queries.h"
}

bool operator<(const peer_id_t& l, const peer_id_t& r)
{
    return l.id < r.id || (l.id == r.id && l.type < r.type);
}

PeersModel::PeersModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void PeersModel::addNewChat(peer_id_t id, peer_t *U)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.append(qMakePair(id, U));
    endInsertRows();
}

int PeersModel::rowCount(const QModelIndex&) const
{
    return m_data.count();
}

QVariant PeersModel::data(const QModelIndex &index, int role) const
{
    const peer_id_t id = m_data.at(index.row()).first;
    const peer_t* data = m_data.at(index.row()).second;
    switch(role)
    {
    case PeerTypeRole:
        return id.type;
    case PeerIdRole:
        return id.id;
    case FirstNameRole:
        Q_ASSERT(id.type == User);
        return data->user.first_name;
    case LastNameRole:
        Q_ASSERT(id.type == User);
        return data->user.last_name;
    case PhoneNumberRole:
        Q_ASSERT(id.type == User);
        return data->user.phone;
    case GroupNameRole:
        Q_ASSERT(id.type == GroupChat);
        return data->chat.title;
    case LastMessageRole:
        return data->last->text;
    case PeerRole:
        return data;
    case Qt::DisplayRole:
        switch (id.type)
        {
        case PEER_CHAT:
            return data->chat.title;
        case PEER_USER:
            return QString("%1 %2").arg(data->user.first_name)
                    .arg(data->user.last_name);
        }
    }

    return QVariant();
}

QHash<int, QByteArray> PeersModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(PeerTypeRole, "peerType");
    roles.insert(PeerIdRole, "peerId");
    roles.insert(FirstNameRole, "firstName");
    roles.insert(LastNameRole, "lastName");
    roles.insert(PhoneNumberRole, "phoneNumber");
    roles.insert(GroupNameRole, "groupName");
    roles.insert(LastMessageRole, "lastMessage");
    roles.insert(PeerRole, "peer");
    return roles;
}
