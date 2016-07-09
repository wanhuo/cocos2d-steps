APP_STL := c++_static
NDK_TOOLCHAIN_VERSION = clang
APP_PLATFORM := android-14
APP_ABI := armeabi armeabi-v7a

APP_CPPFLAGS += -frtti -std=c++11 -fsigned-char -ffunction-sections -fdata-sections -fvisibility=hidden
APP_CXXFLAGS += -std=gnu++11
APP_LDFLAGS += -latomic -Wl,--gc-sections

LOCAL_CFLAGS += -ffunction-sections -fdata-sections -std=c++11

USE_ARM_MODE := 1

ifeq ($(NDK_DEBUG),1)
  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
  APP_OPTIM := debug
else
  APP_CPPFLAGS += -DNDEBUG
  APP_OPTIM := release
endif
