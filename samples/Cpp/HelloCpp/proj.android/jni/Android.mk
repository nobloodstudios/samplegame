LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellocpp_shared

LOCAL_MODULE_FILENAME := libhellocpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../scripting/lua/lua
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../scripting/lua/cocos2dx_support
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes

LOCAL_SRC_FILES := hellocpp/main.cpp \
	../../Classes/AppDelegate.cpp \
	../../Classes/GameController.cpp \
	../../Classes/GameScene.cpp \
	../../Classes/GameObject.cpp \
	../../Classes/DecoratorObject.cpp \
	../../Classes/ConsumableObject.cpp \
	../../Classes/ActorObject.cpp \

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static 
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_lua_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,scripting/lua/proj.android)

