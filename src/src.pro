TEMPLATE = app
TARGET = sahke
CONFIG += sailfishapp debug
HEADERS += telegram.h \
    tgloopthread.h \
    telegram_p.h
#    src/wrapper.h \
#    src/telegramthread.h
SOURCES += sahke.cpp \
    telegram.cpp \
    tgloopthread.cpp \
    telegram_p.cpp

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += ../3rdParty/tg
LIBS += -L../lib -ltg
LIBS += -lcrypto -lz -lrt -lm -lreadline -lssl -llua

#PRE_TARGETDEPS += ../lib/libtg.a
#QMAKE_LFLAGS += -esahke_main
#OBJECTS_DIR = ../o/sahke

#OTHER_FILES += ../qml/sahke.qml \
#    ../qml/cover/CoverPage.qml \
#    ../qml/pages/FirstPage.qml \
#    ../qml/pages/SecondPage.qml \
#    ../qml/pages/AuthorizingPage.qml
#    ../sahke.desktop
#    rpm/sahke.spec \
#    rpm/sahke.yaml \
#    sahke.desktop
