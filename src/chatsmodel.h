#ifndef CHATSMODEL_H
#define CHATSMODEL_H

#include <QMutex>
#include <QAbstractListModel>

#include "structures.h"

class ChatsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ChatsModel(QObject *parent = 0);
    static void onNewChat(void* context, peer_id_t id, peer_t *U);

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index,
                          int role = Qt::DisplayRole) const;

private:
    typedef QList<QPair<peer_id_t,peer_t*>> Container;
    Container m_data;
    mutable QMutex m_dataMutex;
};

#endif // CHATSMODEL_H
