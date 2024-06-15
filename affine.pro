SOURCES += main.cpp xform.cpp
HEADERS += xform.h \
    lispthread.h

QT += widgets

SHARED_FOLDER = ../affine/shared

include($$SHARED_FOLDER/shared.pri)

INCLUDEPATH += ../ecl/msvc/package
LIBS += -L../ecl/msvc/package ecl.lib

RESOURCES += affine.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/painting/affine
INSTALLS += target
