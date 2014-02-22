# The name of your app.
# NOTICE: name defined in TARGET has a corresponding QML filename.
#         If name defined in TARGET is changed, following needs to be
#         done to match new name:
#         - corresponding QML filename must be changed
#         - desktop icon filename must be changed
#         - desktop filename must be changed
#         - icon definition filename in desktop file must be changed
TEMPLATE = subdirs

CONFIG += sailfishapp

SUBDIRS += 3rdParty/tg/tg.pro \
#    3rdParty/config/config.pro \
    sahke

OTHER_FILES += sahke/qml/sahke.qml \
    sahke/qml/cover/CoverPage.qml \
    sahke/qml/pages/FirstPage.qml \
    sahke/qml/pages/SecondPage.qml \
    rpm/sahke.spec \
    rpm/sahke.yaml \
    sahke.desktop \
    3rdParty/tg/tg/tg.pub

#TARGET = sahke

#CONFIG += sailfishapp tg_cli

#SOURCES += src/sahke.cpp

#INCLUDEPATH += 3rdParty/tg

#tg_cli {
#    TG_PATH = 3rdParty/tg
#    INCLUDEPATH += $$TG_PATH
#    HEADERS += $$files($$TG_PATH/*.h)
##    SOURCES += $$files($$TG_PATH/*.c)
#SOURCES += \
##    3rdParty/tg/binlog.c \
#    3rdParty/tg/interface.c \
#    3rdParty/tg/loop.c \
##    3rdParty/tg/lua-tg.c \
##    3rdParty/tg/main.c \
#    3rdParty/tg/mtproto-client.c \
#    3rdParty/tg/mtproto-common.c \
#    3rdParty/tg/net.c \
#    3rdParty/tg/queries.c \
#    3rdParty/tg/structures.c \
#    3rdParty/tg/tools.c
#    LIBS += -lcrypto -lz -lrt -lm -lreadline -llua -lssl
#}

#QMAKE_LFLAGS += -esahke_main

#OTHER_FILES += rpm/sahke.spec \
#    rpm/sahke.yaml \
#    sahke.desktop

#OTHER_FILES += qml/sahke.qml \
#    qml/cover/CoverPage.qml \
#    qml/pages/FirstPage.qml \
#    qml/pages/SecondPage.qml \
#    rpm/sahke.spec \
#    rpm/sahke.yaml \
#    sahke.desktop

