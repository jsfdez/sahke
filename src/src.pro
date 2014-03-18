TEMPLATE = app
TARGET = sahke
!win32 {
    CONFIG += sailfishapp
}
CONFIG += debug
HEADERS += telegram.h \
    telegram_p.h \
    chatsmodel.h \
    chat.h \
    querymethods.h
SOURCES += sahke.cpp \
    telegram.cpp \
    telegram_p.cpp \
    chatsmodel.cpp \
    chat.cpp \
    querymethods.cpp

QMAKE_CXXFLAGS += -std=c++0x -fPIC
PRE_TARGETDEPS += ../lib/libtg.a
INCLUDEPATH += ../3rdParty/tg/tg
LIBS += -L../lib -ltg
LIBS += -lcrypto -lz -lrt -lm -lreadline -lssl
