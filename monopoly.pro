QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    assets.cpp \
    main.cpp \
    model/companytile.cpp \
    model/gotile.cpp \
    model/gotojailtile.cpp \
    model/jailtile.cpp \
    model/luckcard.cpp \
    model/luckcardtile.cpp \
    model/monotile.cpp \
    model/ownabletile.cpp \
    model/parkingtile.cpp \
    model/player.cpp \
    model/propertycolor.cpp \
    model/propertymonopoly.cpp \
    model/propertytile.cpp \
    model/railwaytile.cpp \
    model/taxtile.cpp \
    monopoly.cpp \
    monopolyerrors.cpp \
    ownabletilelist.cpp \
    playerlist.cpp \
    test/TestCounter.cpp \
    test/test.cpp \
    view/colorpickerwidget.cpp \
    view/companywidget.cpp \
    view/cornerwidget.cpp \
    view/gamewindow.cpp \
    view/luckcardwidget.cpp \
    view/mainmenuwindow.cpp \
    view/playercardwidget.cpp \
    view/playerswindow.cpp \
    view/propertywidget.cpp \
    view/railwaywidget.cpp \
    view/rotatingwidget.cpp \
    view/taxwidget.cpp

HEADERS += \
    assets.h \
    model/companytile.h \
    model/gotile.h \
    model/gotojailtile.h \
    model/jailtile.h \
    model/luckcard.h \
    model/luckcardtile.h \
    model/monotile.h \
    model/ownabletile.h \
    model/parkingtile.h \
    model/player.h \
    model/propertycolor.h \
    model/propertymonopoly.h \
    model/propertytile.h \
    model/railwaytile.h \
    model/taxtile.h \
    monopoly.h \
    monopolyerrors.h \
    ownabletilelist.h \
    playerlist.h \
    test/doctest.h \
    view/colorpickerwidget.h \
    view/companywidget.h \
    view/cornerwidget.h \
    view/gamewindow.h \
    view/luckcardwidget.h \
    view/mainmenuwindow.h \
    view/playercardwidget.h \
    view/playerswindow.h \
    view/propertywidget.h \
    view/railwaywidget.h \
    view/rotatingwidget.h \
    view/taxwidget.h \
    view/tilerotation.h

FORMS += \
    view/colorpickerwidget.ui \
    view/gamewindow.ui \
    view/mainmenuwindow.ui \
    view/playercardwidget.ui \
    view/playerswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    assets/PlayerPieceXY.png \
    assets/chance.txt \
    assets/colors.txt \
    assets/community_chest.txt \
    assets/images/die1.png \
    assets/images/die2.png \
    assets/images/die3.png \
    assets/images/die4.png \
    assets/images/die5.png \
    assets/images/die6.png \
    assets/images/dieBase.png \
    assets/images/electric.png \
    assets/images/go.png \
    assets/images/goOLD.png \
    assets/images/goto-jail.png \
    assets/images/hotel.png \
    assets/images/house.png \
    assets/images/jail-icon.png \
    assets/images/jail.png \
    assets/images/jailOLD.png \
    assets/images/parking.png \
    assets/images/railway.png \
    assets/images/tax.png \
    assets/images/water.png \
    assets/spaces.txt
