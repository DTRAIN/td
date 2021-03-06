ENGINE_HDRS +=  ./engine/Collectable.h \
                ./engine/Driver.h \
                ./engine/Effect.h \
                ./engine/EffectTypes.h \
                ./engine/GameObject.h \
                ./engine/Map.h \
                ./engine/NPC.h \
                ./engine/NPCWave.h \
                ./engine/Player.h \
                ./engine/Projectile.h \
                ./engine/ResManager.h \
                ./engine/Tile.h \
                ./engine/TileExtension.h \
                ./engine/Tower.h \
                ./engine/BuildingTower.h \
                ./engine/Resource.h \
                ./engine/Unit.h \
                ./engine/Parser.h


ENGINE_SRCS +=  ./engine/Collectable.cpp \
                ./engine/Driver.cpp \
                ./engine/Effect.cpp \
                ./engine/EffectTypes.cpp \
                ./engine/GameObject.cpp \
                ./engine/Map.cpp \
                ./engine/NPC.cpp \
                ./engine/NPCWave.cpp \
                ./engine/Player.cpp \
                ./engine/Projectile.cpp \
                ./engine/ResManager.cpp \
                ./engine/Tile.cpp \
                ./engine/TileExtension.cpp \
                ./engine/Tower.cpp \
                ./engine/BuildingTower.cpp \
                ./engine/Resource.cpp \
                ./engine/Unit.cpp \
                ./engine/Parser.cpp

# Client-side engine headers and sources
ENGINE_HDRS_C +=    $$ENGINE_HDRS \
                    ./engine/ContextMenu.h \
                    ./engine/ContextMenuTypes.h \
                    ./engine/CDriver.h

ENGINE_SRCS_C +=    $$ENGINE_SRCS \
                    ./engine/ContextMenu.cpp \
                    ./engine/ContextMenuTypes.cpp \
                    ./engine/CDriver.cpp

# Server-side engine headers and sources
ENGINE_HDRS_S +=    $$ENGINE_HDRS \
                    ./engine/SDriver.h

ENGINE_SRCS_S +=    $$ENGINE_SRCS \
                    ./engine/SDriver.cpp
