#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include "structures.h"

class Peer : public QObject
{
    Q_OBJECT
    Q_ENUMS(PeerType)
    Q_PROPERTY(int id READ id NOTIFY idChanged)
    Q_PROPERTY(PeerType peerType READ peerType NOTIFY peerTypeChanged)
    Q_PROPERTY(QString firstName READ firstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName NOTIFY lastNameChanged)

public:
    enum PeerType
    {
        PeerUnknown = PEER_UNKNOWN,
        PeerUser = PEER_USER,
        PeerChat = PEER_CHAT,
        PeerGeoChat = PEER_CHAT,
        PeerEncriptedChat = PEER_ENCR_CHAT
    };

    explicit Peer(QObject *parent = 0);
    explicit Peer(peer_id_t id, peer_t* data, QObject *parent = 0);

    int id() const;
    PeerType peerType() const;

    QString firstName() const;
    QString lastName() const;

signals:
    void idChanged();
    void peerTypeChanged();
    void firstNameChanged();
    void lastNameChanged();

private:
    peer_id_t m_id;
    peer_t* m_data;
};

#endif // CHAT_H
