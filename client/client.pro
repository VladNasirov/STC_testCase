QT = core network xml gui widgets

CONFIG += c++17 cmdline
#DEFINES +=DEBUG_LOG
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        client.cpp \
        ../dto/dtogenerator.cpp \
        clientgui.cpp \
        main.cpp \
        ../xml/xmlparser.cpp


HEADERS += \
    client.h \
    ../dto/dtogenerator.h \
    clientgui.h \
    ../xml/xmlparser.h
