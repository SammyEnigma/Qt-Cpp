TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

mac : {
    QMAKE_RPATHDIR += /Users/gauravkumar/dependencies/Dist/lib

    INCLUDEPATH +=/Users/gauravkumar/dependencies/Dist/include
    LIBS += -L/Users/gauravkumar/dependencies/Dist/lib

    LIBS += -ldlib -lcblas -llapack
}

