TARGET =dvb-p-si2
TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    csvdata.cpp \
    fileparser.cpp \
    tsreader.cpp \
    dvbdumpreader.cpp \
    csvreader.cpp \
    sectioncrc.c \
    DVB/dvb_section.cpp \
    DVB/utils.cpp \
    DVB/tables.cpp

RESOURCES += qml.qrc
## Dinesh: comment following line while making tag release
QMAKE_CXXFLAGS += -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    csvdata.h \
    fileparser.h \
    tsreader.h \
    dvbdumpreader.h \
    csvreader.h \
    sectioncrc.h \
    DVB/dvb_section.hpp \
    DVB/tables.hpp \
    DVB/utils.h

DISTFILES += \
    PrarsingRules.txt
