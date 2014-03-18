#ifndef CHAT_H
#define CHAT_H

#include <QAbstractListModel>

#include "querymethods.h"

extern "C" {
#include "queries.h"
#include "structures.h"
}

class ChatModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(Roles)
    Q_ENUMS(Action)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)

public:
    enum Roles {
        TextRole = Qt::UserRole + 1,
        DateRole,
        FromRole,
        ActionRole
    };

    enum Action {
        Message = 0,
        ChatCreated,
        ChatChangeTitle,
        ChatChangePhoto,
        ChatDeletePhoto,
        ChatAddUser,
        ChatDeleteUser,

        NotSupported
    };

    ChatModel(QObject* parent = 0);

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex& index,
                          int role = Qt::DisplayRole) const;
    virtual QHash<int,QByteArray> roleNames() const;

    Q_INVOKABLE bool loadChat(int type, int id);
    Q_INVOKABLE void sendText(const QString& text);

    QString title() const;

signals:
    void titleChanged();

private:
    typedef QueryMethodsBase<ChatModel> QueryMethods;

    static int onReceivedChatHistory(struct query *q);
    Q_INVOKABLE void updateChat();

    void getChatHistory(peer_id_t id);
    void getDifference();
    Action mapToAction(int code) const;

    message* messageIndex(int row) const;
    int m_type;
    int m_id;
    peer_t* m_peer;
    QHash<int,QString> m_names;
};

#endif // CHAT_H
