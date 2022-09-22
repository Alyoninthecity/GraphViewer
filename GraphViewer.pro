QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphViewer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNING

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    datamodel.cpp \
    basechart.cpp \
    graphviewer.cpp \
    controller.cpp \
    barchart.cpp \
    doc.cpp \
    piechart.cpp \
    linechart.cpp \
    areachart.cpp \
    scatterchart.cpp \
    aboutus.cpp \
    polarchart.cpp

HEADERS += \
    datamodel.h \
    basechart.h \
    graphviewer.h \
    controller.h \
    barchart.h \
    doc.h \
    piechart.h \
    linechart.h \
    areachart.h \
    scatterchart.h \
    aboutus.h \
    polarchart.h

RESOURCES += \
    src.qrc


