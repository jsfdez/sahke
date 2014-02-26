#include "chatsmodel.h"

bool operator<(const peer_id_t& l, const peer_id_t& r)
{
    return l.id < r.id || (l.id == r.id && l.type < r.type);
}

ChatsModel::ChatsModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void ChatsModel::onNewChat(void *context, peer_id_t id, peer_t *U)
{
    ChatsModel* c = reinterpret_cast<ChatsModel*>(context);
    QMutexLocker locker(&c->m_dataMutex);

    c->beginInsertRows(QModelIndex(), c->rowCount(), c->rowCount());
    c->m_data.append(qMakePair(id, U));
    c->endInsertRows();
}

int ChatsModel::rowCount(const QModelIndex&) const
{
    QMutexLocker locker(&m_dataMutex);
    return m_data.count();
}

QVariant ChatsModel::data(const QModelIndex &index, int role) const
{
    QMutexLocker locker(&m_dataMutex);
    const peer_t* data = m_data.at(index.row()).second;
    switch(role)
    {
    case Qt::DisplayRole:
        return QString("%s %s").arg(data->user.first_name)
                .arg(data->user.last_name);
    }

    return QVariant();
}
