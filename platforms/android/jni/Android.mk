LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := core_shared

LOCAL_MODULE_FILENAME := libcore

LOCAL_SRC_FILES := application.cpp \
                   ../../../../cocos2d-tooflya-sdk/AppDelegate.cpp \
                   ../../../../cocos2d-tooflya-sdk/actions/Shake.cpp \
                   ../../../../cocos2d-tooflya-sdk/audio/Music.cpp \
                   ../../../../cocos2d-tooflya-sdk/audio/Sound.cpp \
                   ../../../../cocos2d-tooflya-sdk/backgrounds/Background.cpp \
                   ../../../../cocos2d-tooflya-sdk/backgrounds/BackgroundColor.cpp \
                   ../../../../cocos2d-tooflya-sdk/backgrounds/BackgroundScroll.cpp \
                   ../../../../cocos2d-tooflya-sdk/backgrounds/BackgroundPages.cpp \
                   ../../../../cocos2d-tooflya-sdk/entities/Entity.cpp \
                   ../../../../cocos2d-tooflya-sdk/entities/TiledEntity.cpp \
                   ../../../../cocos2d-tooflya-sdk/entities/Entity3D.cpp \
                   ../../../../cocos2d-tooflya-sdk/entities/AnimatedEntity.cpp \
                   ../../../../cocos2d-tooflya-sdk/entities/BatchEntity.cpp \
                   ../../../../cocos2d-tooflya-sdk/entities/Button.cpp \
                   ../../../../cocos2d-tooflya-sdk/entities/Motion.cpp \
                   ../../../../cocos2d-tooflya-sdk/entities/Text.cpp \
                   ../../../../cocos2d-tooflya-sdk/entities/Spine.cpp \
                   ../../../../cocos2d-tooflya-sdk/entities/ParallaxEntity.cpp \
                   ../../../../cocos2d-tooflya-sdk/missions/Missions.cpp \
                   ../../../../cocos2d-tooflya-sdk/parallax/ParallaxPool.cpp \
                   ../../../../cocos2d-tooflya-sdk/pools/Pool.cpp \
                   ../../../../cocos2d-tooflya-sdk/screens/Screen.cpp \
                   ../../../../cocos2d-tooflya-sdk/translate/Translate.cpp \
                   ../../../../cocos2d-tooflya-sdk/support/Events.cpp \
                   ../../../../cocos2d-tooflya-sdk/support/Config.cpp \
                   ../../../../cocos2d-tooflya-sdk/platform/android/analytics/Analytics.cpp \
                   ../../../../cocos2d-tooflya-sdk/platform/android/batch/Batch.cpp \
                   ../../../../cocos2d-tooflya-sdk/platform/android/heyzap/Heyzap.cpp \
                   ../../../../cocos2d-tooflya-sdk/platform/android/internal/Internal.cpp \
                   ../../../../cocos2d-tooflya-sdk/platform/include/internal/Internal.cpp \
                   ../../../../cocos2d-tooflya-sdk/platform/android/media/Media.cpp \
                   ../../../../cocos2d-tooflya-sdk/platform/android/modal/Modal.cpp \
                   ../../../../cocos2d-tooflya-sdk/platform/android/purchase/Purchase.cpp \
                   ../../../../cocos2d-tooflya-sdk/platform/android/screenshot/Screenshot.cpp \
                   ../../../../cocos2d-tooflya-sdk/platform/android/services/Services.cpp \
                   ../../../../cocos2d-tooflya-sdk/platform/include/services/Services.cpp \
                   ../../../../cocos2d-tooflya-sdk/platform/android/social/Social.cpp \
                   ../../../../cocos2d-tooflya-sdk/platform/include/vote/Vote.cpp \
                   ../../../../cocos2d-tooflya-sdk/platform/android/vote/Vote.cpp \
                   ../../../sources/entities/Environment.cpp \
                   ../../../sources/entities/Generator.cpp \
                   ../../../sources/entities/Route.cpp \
                   ../../../sources/entities/Cube.cpp \
                   ../../../sources/entities/Character.cpp \
                   ../../../sources/entities/Plate.cpp \
                   ../../../sources/entities/Particle.cpp \
                   ../../../sources/entities/Number.cpp \
                   ../../../sources/entities/Counter.cpp \
                   ../../../sources/entities/Decoration.cpp \
                   ../../../sources/entities/Diamond.cpp \
                   ../../../sources/entities/Spike.cpp \
                   ../../../sources/entities/Fish.cpp \
                   ../../../sources/entities/Ripple.cpp \
                   ../../../sources/entities/Ship.cpp \
                   ../../../sources/support/Events.cpp \
                   ../../../sources/screens/Game.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../cocos2d/cocos/audio/include \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/actions \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/audio \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/backgrounds \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/entities \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/parallax \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/pools \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/screens \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/support \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/translate \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/platform \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/platform/include \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/platform/include/analytics \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/platform/include/batch \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/platform/include/heyzap \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/platform/include/internal \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/platform/include/media \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/platform/include/modal \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/platform/include/purchase \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/platform/include/screenshot \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/platform/include/services \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/platform/include/social \
                    $(LOCAL_PATH)/../../../../cocos2d-tooflya-sdk/platform/include/vote \
                    $(LOCAL_PATH)/../../../sources/entities \
                    $(LOCAL_PATH)/../../../sources/popups \
                    $(LOCAL_PATH)/../../../sources/screens \
                    $(LOCAL_PATH)/../../../sources/support \

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos)
