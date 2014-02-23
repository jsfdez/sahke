TEMPLATE = app
TARGET = sahke
CONFIG += sailfishapp debug
HEADERS += src/wrapper.h \
    src/telegram.h \
    src/telegramthread.h
SOURCES += src/sahke.cpp \
#    ../3rdParty/tg/mtproto-common.c \
#    ../3rdParty/tg/mtproto-client.c \
#    ../3rdParty/tg/net.c \
#    ../3rdParty/tg/tools.c \
#    ../3rdParty/tg/structures.c \
##    ../3rdParty/tg/binlog.c \
#    src/wrapper.c
    src/telegram.cpp \
    src/telegramthread.cpp

#QMAKE_CXXFLAGS += -fplan9-extensions
#QMAKE_CFLAGS_DEBUG += -fplan9-extensions
#QMAKE_CFLAGS_RELEASE += -fplan9-extensions

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += ../3rdParty/tg
LIBS += -L../lib -ltg
LIBS += -lcrypto -lz -lrt -lm -lreadline -lssl

#PRE_TARGETDEPS += ../lib/libtg.a
#QMAKE_LFLAGS += -esahke_main
#OBJECTS_DIR = ../o/sahke

OTHER_FILES += ../qml/sahke.qml \
    ../qml/cover/CoverPage.qml \
    ../qml/pages/FirstPage.qml \
    ../qml/pages/SecondPage.qml \
    ../qml/pages/AuthorizingPage.qml
#    ../sahke.desktop
#    rpm/sahke.spec \
#    rpm/sahke.yaml \
#    sahke.desktop
