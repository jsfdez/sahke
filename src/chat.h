#ifndef CHAT_H
#define CHAT_H

#include <QAbstractListModel>

extern "C" {
#include "structures.h"
#include "queries.h"
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
    Q_INVOKABLE void sendText(const QString& text);

private:
    struct QueryMethods : query_methods {
        QueryMethods(ChatModel* ctx)
        {
            context = ctx;
            on_answer = nullptr;
            on_error = nullptr;
            on_timeout = nullptr;
        }

        ChatModel* context;
        peer_id_t peerId;
    };

    static int onReceivedChatHistory(struct query *q);
    Q_INVOKABLE void updateChat();

    void getChatHistory(peer_id_t id);

    message* messageIndex(int row) const;
    int m_type;
    int m_id;
    peer_t* m_peer;
    QHash<int,QString> m_names;
};

#endif // CHAT_H
