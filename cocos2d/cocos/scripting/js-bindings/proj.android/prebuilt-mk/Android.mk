LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2d_js_android_static

LOCAL_MODULE_FILENAME := libjscocos2dandroid

ifeq ($(COCOS_SIMULATOR_BUILD),1)
LOCAL_ARM_MODE := arm
endif

LOCAL_SRC_FILES := ..\..\..\..\..\prebuilt\android/$(TARGET_ARCH_ABI)/libjscocos2dandroid.a


LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -lz \
                       -landroid

LOCAL_WHOLE_STATIC_LIBRARIES := spidermonkey_static

include $(PREBUILT_STATIC_LIBRARY)

#==============================================================

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2d_js_static

LOCAL_MODULE_FILENAME := libjscocos2d

LOCAL_SRC_FILES := ..\..\..\..\..\prebuilt\android/$(TARGET_ARCH_ABI)/libjscocos2d.a


LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT



LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../manual \
$(LOCAL_PATH)/../../manual/navmesh \
$(LOCAL_PATH)/../../auto \
$(LOCAL_PATH)/../../../../audio/include

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2d_js_android_static

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_localstorage_static

include $(PREBUILT_STATIC_LIBRARY)

$(call import-module, ./prebuilt-mk)
$(call import-module,external/spidermonkey/prebuilt/android)
$(call import-module, storage/local-storage/prebuilt-mk)
