TEMPLATE = app
TARGET = sahke
!win32 {
    CONFIG += sailfishapp
}
CONFIG += debug
HEADERS += telegram.h \
    telegram_p.h
SOURCES += sahke.cpp \
    telegram.cpp \
    telegram_p.cpp
#    lua-tg.cpp

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += ../3rdParty/tg/tg
LIBS += -L../lib -ltg
LIBS += -lcrypto -lz -lrt -lm -lreadline -lssl -llua
