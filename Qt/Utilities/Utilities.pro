QT += core
QT += gui

CONFIG += c++11

TARGET = Utilities
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    utilities.h \
    polygon_utils.h \
    common_imports.h
