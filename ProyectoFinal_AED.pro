QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    amigos.cpp \
    comentarios.cpp \
    m_feed.cpp \
    main.cpp \
    m_menu.cpp \
    matched_users.cpp \
    publicacion.cpp \
    registro.cpp

HEADERS += \
    Bst.h \
    Lista.h \
    amigos.h \
    comentarios.h \
    m_feed.h \
    m_menu.h \
    matched_users.h \
    node_user.h \
    publicacion.h \
    registro.h

FORMS += \
    amigos.ui \
    comentarios.ui \
    m_feed.ui \
    m_menu.ui \
    matched_users.ui \
    publicacion.ui \
    registro.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    add_frend.qrc \
    botones.qrc \
    fotos.qrc \
    logo_icon.qrc
