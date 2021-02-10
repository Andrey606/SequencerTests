include(gtest_dependency.pri)

QT += core network mqtt sql testlib

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
QT       += core
QT       += network
QT       += sql
LIBS += -lyaml-cpp
QT -= gui
QT += mqtt testlib

INCLUDEPATH += ../sequencer

HEADERS += \
        ../sequencer/ComandParserdef.h \
        ../sequencer/IR/CarrierHeatpumpIR.h \
        ../sequencer/IR/HeatpumpIR.h \
        ../sequencer/IR/IRSender.h \
        ../sequencer/IR/MitsubishiHeatpumpIR.h \
        ../sequencer/IR/MitsubishiHeavyHeatpumpIR.h \
        ../sequencer/IR/ToshibaDaiseikaiHeatpumpIR.h \
        ../sequencer/IR_module.h \
        ../sequencer/Log/LoggingCategories.h \
        ../sequencer/ZigbeeConstant.h \
        ../sequencer/buffer.h \
        ../sequencer/clientconnection.h \
        ../sequencer/colordebug.h \
        ../sequencer/db.h \
        ../sequencer/device_list.h \
        ../sequencer/device_manager/deviceAutoAdding.h \
        ../sequencer/device_manager/device_types.h \
        ../sequencer/device_manager/devices.h \
        ../sequencer/device_manager/re_adding_omo_devices.h \
        ../sequencer/jsonobject.h \
        ../sequencer/message.h \
        ../sequencer/deviceFactory.h \
        ../sequencer/sequencer.h \
        ../sequencer/shellAdmin.h \
        ../sequencer/shellhost.h \
        ../sequencer/shellserver.h \
        ../sequencer/shellvoice.h \
        ../sequencer/signalManager.h \
        ../sequencer/tuyaParser.h \
        ../sequencer/webserver.h \
        tst_device.h \
        tst_device_intercom.h \
        tst_message.h

SOURCES += \
        ../sequencer/IR/CarrierHeatpumpIR.cpp \
        ../sequencer/IR/HeatpumpIR.cpp \
        ../sequencer/IR/IRSender.cpp \
        ../sequencer/IR/IRSenderBitBang.cpp \
        ../sequencer/IR/IRSenderBlaster.cpp \
        ../sequencer/IR/IRSenderPWM.cpp \
        ../sequencer/IR/MitsubishiHeatpumpIR.cpp \
        ../sequencer/IR/MitsubishiHeavyHeatpumpIR.cpp \
        ../sequencer/IR/ToshibaDaiseikaiHeatpumpIR.cpp \
        ../sequencer/Log/LoggingCategories.cpp \
        ../sequencer/buffer.cpp \
        ../sequencer/clientconnection.cpp \
        ../sequencer/colordebug.cpp \
        ../sequencer/db.cpp \
        ../sequencer/deviceFactory.cpp \
        ../sequencer/device_list.cpp \
        ../sequencer/device_manager/deviceAutoAdding.cpp \
        ../sequencer/device_manager/devices.cpp \
        ../sequencer/device_manager/re_adding_omo_devices.cpp \
        ../sequencer/jsonobject.cpp \
        ../sequencer/message.cpp \
        ../sequencer/sequencer.cpp \
        ../sequencer/shellAdmin.cpp \
        ../sequencer/shellhost.cpp \
        ../sequencer/shellserver.cpp \
        ../sequencer/shellvoice.cpp \
        ../sequencer/signalManager.cpp \
        ../sequencer/tuyaParser.cpp \
        ../sequencer/webserver.cpp \
        main.cpp
