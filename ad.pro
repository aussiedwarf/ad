TEMPLATE = lib
CONFIG += static
CONFIG += c++11
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -stdlib=libc++

DEBUG_DIR =
RELEASE_DIR =
COMPILER_STR =
ARCH_STR = x64
DESTDIR =

win32-g++{
    COMPILER_STR = win32-g++
}

linux-g++-64{
    COMPILER_STR = linux-g++
}

linux-g++{
    COMPILER_STR = linux-g++
}

macx{
    COMPILER_STR = macx


    INCLUDEPATH += /Library/Frameworks/SDL2
    INCLUDEPATH += /Library/Frameworks/SDL2_image/SDL2_image.framework/Headers
    INCLUDEPATH += /Library/Frameworks/SDL2_ttf/SDL2_ttf.framework/Headers
}
contains(QMAKE_HOST.arch, x86_64):{
    ARCH_STR = x64
}


DEBUG_DIR = builds/$${COMPILER_STR}_$${ARCH_STR}/debug
RELEASE_DIR = builds/$${COMPILER_STR}_$${ARCH_STR}/release

CONFIG(release, debug|release): {
    DESTDIR = $${RELEASE_DIR}
}
CONFIG(debug, debug|release): {
    DESTDIR = $${DEBUG_DIR}
}

OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/qrc
UI_DIR = $$DESTDIR/ui


release {
  QMAKE_CXXFLAGS_RELEASE -= -O2
  QMAKE_CXXFLAGS_RELEASE += -O3
}



INCLUDEPATH +=\
    adCore \
    adPlatform \
    adText \
    adGui \
    ../GLM/glm-0.9.4.3

SOURCES +=      \
                adCore/adView.cpp \
                adCore/adWindow.cpp \
                adCore/adImage.cpp \
                adText/adText.cpp \
                adText/adFont.cpp \
                adText/adFontLib.cpp \
                adText/adPrintLib.cpp


HEADERS +=      adPlatform/adPlatform.h \
                adPlatform/adOpenGL.h \
                adCore/adView.h \
                adCore/adWindow.h \
                adCore/adImage.h \
                adText/adText.h \
                adText/adFont.h \
                adText/adFontLib.h \
                adText/adPrintLib.h \
                adText/adTextShader.h






