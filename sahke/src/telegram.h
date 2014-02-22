#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <QObject>

class Telegram : public QObject
{
    Q_OBJECT
public:
    explicit Telegram(QObject *parent = 0);

public slots:
    bool start();
};

#endif // TELEGRAM_H
