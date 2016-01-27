APP_STL := gnustl_static

APP_ABI := armeabi armeabi-v7a

APP_CPPFLAGS += -frtti -std=c++11 -fsigned-char -ffunction-sections -fdata-sections -fvisibility=hidden
APP_LDFLAGS += -latomic -Wl,--gc-sections

LOCAL_CFLAGS += -ffunction-sections -fdata-sections

USE_ARM_MODE := 1

ifeq ($(NDK_DEBUG),1)
  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
  APP_OPTIM := debug
else
  APP_CPPFLAGS += -DNDEBUG
  APP_OPTIM := release
endif
