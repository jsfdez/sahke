#ifndef CHATSMODEL_H
#define CHATSMODEL_H

#include <QMutex>
#include <QAbstractListModel>

#include "structures.h"

class ChatsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(PeerType)

public:
    enum PeerType {
        User = PEER_USER,
        GroupChat = PEER_CHAT
    };
    explicit ChatsModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index,
                          int role = Qt::DisplayRole) const;
    virtual QHash<int,QByteArray> roleNames() const;

public slots:
    void addNewChat(peer_id_t id, peer_t *U);

signals:
    void newChatReceived(peer_id_t id, peer_t *U);

private:
    enum Roles
    {
        PeerTypeRole = Qt::UserRole + 1,
        FirstNameRole,
        LastNameRole,
        PhoneNumberRole,
        GroupNameRole,
        LastMessageRole
    };

    typedef QList<QPair<peer_id_t,peer_t*>> Container;
    Container m_data;
};

#endif // CHATSMODEL_H
