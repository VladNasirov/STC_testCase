QT = core network xml gui widgets

CONFIG += c++17 cmdline
#DEFINES +=DEBUG_LOG
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        server.cpp \
        ../dto/dtogenerator.cpp \
        main.cpp \
        ../xml/xmlparser.cpp \
        servergui.cpp \
        xmlthread.cpp


HEADERS += \
    server.h \
    ../dto/dtogenerator.h \
    ../xml/xmlparser.h \
    servergui.h \
    xmlthread.h
