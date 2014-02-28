#include "chat.h"

#include <QDebug>

Peer::Peer(QObject *parent)
    : QObject(parent)
    , m_id({0, -1})
    , m_data(nullptr)
{

}

Peer::Peer(peer_id_t id, peer_t* data, QObject *parent)
    : QObject(parent)
    , m_id(id)
    , m_data(data)
{
    emit idChanged();
    emit peerTypeChanged();
    emit firstNameChanged();
    emit lastNameChanged();
}

int Peer::id() const
{
    return m_id.id;
}

Peer::PeerType Peer::peerType() const
{
    return static_cast<PeerType>(m_id.type);
}

QString Peer::firstName() const
{
    qDebug() << "FIRST NAME: " << m_data->user.first_name;
    return m_data->user.first_name;
}

QString Peer::lastName() const
{
    return m_data->user.last_name;
}
