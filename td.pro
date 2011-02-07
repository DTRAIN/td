######################################################################
# Automatically generated by qmake (2.01a) Wed Jan 26 20:18:46 2011
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
DESTDIR = ./bin

macx {
    LIBS += -framework OpenAL
    CONFIG += link_pkgconfig
    PKGCONFIG = vorbisfile vorbis
}

unix:!macx {
    CONFIG += link_pkgconfig
    PKGCONFIG = openal vorbisfile vorbis
}

AUDIO_HDRS +=   src/audio/manager.h \
                src/audio/openal_helper.h

AUDIO_SRCS +=   src/audio/manager.cpp \
                src/audio/openal_helper.cpp
                
NETWORK_HDRS += src/network/netclient.h \
                src/network/stream.h

NETWORK_SRCS += src/network/stream.cpp \
                src/network/netclient.cpp
                
ENGINE_HDRS +=  src/engine/CDriver.h \
                src/engine/GameObject.h \
                src/engine/InputComponent.h \
                src/engine/PlayerInputComponent.h \
                src/engine/PhysicsComponent.h \
                src/engine/Player.h \
                src/engine/PlayerPhysicsComponent.h \
                src/engine/SDriver.h \
                src/engine/Tile.h \
                src/engine/Unit.h
                
ENGINE_SRCS +=  src/engine/CDriver.cpp \
                src/engine/GameObject.cpp \
                src/engine/InputComponent.cpp \
                src/engine/PlayerInputComponent.cpp \
                src/engine/PhysicsComponent.cpp \
                src/engine/Player.cpp \
                src/engine/PlayerPhysicsComponent.cpp \
                src/engine/SDriver.cpp \
                src/engine/Unit.cpp



HEADERS += $$AUDIO_HDRS $$NETWORK_HDRS $$ENGINE_HDRS
SOURCES += src/main.cpp $$AUDIO_SRCS $$NETWORK_SRCS $$ENGINE_SRCS
