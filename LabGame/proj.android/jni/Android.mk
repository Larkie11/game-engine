LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/AnimationManager.cpp \
				   ../../Classes/AudioManager.cpp \
				   ../../Classes/Character.cpp \
				   ../../Classes/Instructions.cpp \
				   ../../Classes/MenuScene.cpp \
				   ../../Classes/PlayerMonsterDatabase.cpp \
				   ../../Classes/SceneManager.cpp \
				   ../../Classes/SelectLevelScene.cpp \
				   ../../Classes/Settings.cpp \
				   ../../Classes/Shop.cpp \
				   ../../Classes/Touchables.cpp \
				   ../../Classes/Player.cpp \
				   ../../Classes/UpgradeScreen.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
