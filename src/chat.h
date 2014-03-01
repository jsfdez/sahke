#ifndef CHAT_H
#define CHAT_H

#include <QAbstractListModel>

extern "C" {
#include "structures.h"
}

class ChatModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(Roles)

public:
    enum Roles {
        MessageRole = Qt::UserRole + 1,
        DateRole,
        FromRole
    };

    ChatModel(QObject* parent = 0);

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex& index,
                          int role = Qt::DisplayRole) const;
    virtual QHash<int,QByteArray> roleNames() const;

    Q_INVOKABLE bool loadChat(int type, int id);

private:
    message* messageIndex(int row) const;
    int m_type;
    int m_id;
    peer_t* m_peer;
    QHash<int,QString> m_names;
};

#endif // CHAT_H
