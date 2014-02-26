TARGET = tg
QT -= gui
TEMPLATE = lib
CONFIG = plugin static debug
DESTDIR = ../../lib

QMAKE_CFLAGS_DEBUG += -fno-strict-aliasing
QMAKE_CFLAGS_RELEASE += -fno-strict-aliasing
DEFINES += 'PROG_NAME=\'\"sahke\"\''
DEFINES += LIB_TG

INCLUDEPATH += tg

HEADERS += $$files(tg/*.h)
SOURCES += \
    tg/binlog.c \
    tg/interface.c \
    tg/loop.c \
    tg/lua-tg.c \
    tg/main.c \
    tg/mtproto-client.c \
    tg/mtproto-common.c \
    tg/net.c \
    tg/queries.c \
    tg/structures.c \
    tg/tools.c

LIBS += -lcrypto -lz -lrt -lm -lreadline -lssl
LIBS += -llua
