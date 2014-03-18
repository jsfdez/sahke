/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#ifndef Q_OS_CYGWIN
#include <sailfishapp.h>
#endif
#include <QGuiApplication>

#include "chat.h"
#include "telegram.h"
#include "chatsmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication* app;
    QQuickView* view;

    qmlRegisterType<PeersModel>("Telegram", 1, 0, "ChatsModel");
    qmlRegisterType<ChatModel>("Telegram", 1, 0, "Chat");
//    qmlRegisterType<peer_t*>("Telegram", 1, 0, "Peer");
    qRegisterMetaType<peer_id_t>("peer_id_t");
    qRegisterMetaType<peer_t*>("peer_t*");
    qRegisterMetaType<QList<ChatModel*>>("PeerList");

#ifdef Q_OS_CYGWIN
    app = new QGuiApplication(argc, argv);
    view = new QQuickView;
#else
    app = SailfishApp::application(argc, argv);
    view = SailfishApp::createView();
#endif

    view->engine()->rootContext()->setContextProperty(
                "telegram", Telegram::instance());
    view->engine()->rootContext()->setContextProperty("debug", QVariant(true));
#ifdef Q_OS_CYGWIN
    view->setSource(QUrl::fromLocalFile("win/qml/sahke.qml");
#else
    view->setSource(SailfishApp::pathTo("qml/sahke.qml"));
#endif
    view->show();

    return app->exec();
}

