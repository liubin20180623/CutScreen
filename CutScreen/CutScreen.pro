QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
RC_ICONS = $$PWD/resources/images/app.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwidget.cpp

HEADERS += \
    mainwidget.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# 子工程

include ($$PWD/qtrayicon/qtrayicon.pri)
include ($$PWD/qscreenview/qscreenview.pri)
include ($$PWD/qhook/qhook.pri)
include ($$PWD/qtool/qtool.pri)
include ($$PWD/qconfig/qconfig.pri)


# 附加包含路径
INCLUDEPATH += \
           $$PWD/qconfig \
           $$PWD/qtrayicon \
           $$PWD/qscreenview \
           $$PWD/qhook \
           $$PWD/qtool \

# 依赖模块
LIBS += \
         -L$$PWD/qhook/ -lGridWndHook\
         -luser32\

# 输出目录
CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/output/debug
} else {
    QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\"
    DESTDIR = $$PWD/output/release
}

RESOURCES += \
    resources/resource.qrc


