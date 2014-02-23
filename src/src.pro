TEMPLATE = app
TARGET = sahke
!win32 {
    CONFIG += sailfishapp
}
CONFIG += debug
HEADERS += telegram.h \
    tgloopthread.h \
    telegram_p.h
SOURCES += sahke.cpp \
    telegram.cpp \
    tgloopthread.cpp \
    telegram_p.cpp

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += ../3rdParty/tg
LIBS += -L../lib -ltg
LIBS += -lcrypto -lz -lrt -lm -lreadline -lssl -llua
