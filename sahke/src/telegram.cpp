#include "telegram.h"

#include <QDebug>

extern long long pk_fingerprint;

extern "C" {
extern void on_start();
}

Telegram::Telegram(QObject *parent) :
    QObject(parent)
{
    qDebug() << "Creating Telegram Object";
}

bool Telegram::start()
{
    pk_fingerprint = 0;
    on_start();

    if (pk_fingerprint != 0)
    {
        qDebug() << "Public key loaded";
    }
    return pk_fingerprint != 0;
}
