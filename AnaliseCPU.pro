QT += core
QT -= gui

TARGET = AnaliseCPU
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

CONFIG  += c++11
LIBS += -pthread
