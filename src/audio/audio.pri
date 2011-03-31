AUDIO_HDRS +=   ./audio/manager.h \
                ./audio/openal_helper.h \
                ./audio/SfxManager.h

AUDIO_SRCS +=   ./audio/manager.cpp \
                ./audio/openal_helper.cpp \
                ./audio/SfxManager.cpp

win32 {
    LIBS += OpenAL32.lib libogg.lib libvorbisfile.lib libvorbis.lib
}
macx {
    LIBS += -framework OpenAL
    CONFIG += link_pkgconfig
    PKGCONFIG = vorbisfile vorbis
}
unix:!macx {
    CONFIG += link_pkgconfig
    PKGCONFIG = openal vorbisfile vorbis
}
