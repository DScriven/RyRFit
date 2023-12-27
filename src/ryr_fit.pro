
OBJECTS_DIR   = obj
MOC_DIR       = moc
QT +=widgets opengl multimedia

CONFIG += release c++17

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

HEADERS       = ryr_fit4.h   \
                interface.h \
                tetramer.h \
                tiff6qt.h
SOURCES       =   \
                interface.cpp \
                ryr_fit4.cpp \
                ryr_fit4_main.cpp    \
                tiff6qt.cpp
FORMS  =  interface.ui

RESOURCES=ryr_fit.qrc

# install
win32 {
RC_FILE = RyRFit_resource.rc
LIBS += "C:/dev/CGAL-5.5.1/auxiliary/gmp/lib/gmp.lib"
LIBS += "C:/dev/boost_1_81_0/lib64-msvc-14.2/libboost_system-vc142-mt-x64-1_81.lib"
LIBS +=  "C:/dev/tiff-4.0.10/libtiff/libtiff.lib"
INCLUDEPATH += "C:/dev/tiff-4.0.10/libtiff"
INCLUDEPATH += "C:/dev/CGAL-5.5.1/include" "C:/dev/boost_1_81_0"
}
unix{
LIBS+= -lboost_system -ltiff  -lgmp
}
TARGET = RyRFit
