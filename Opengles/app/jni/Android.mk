LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := glapi
#LOCAL_CFLAGS    := -Wall -Wextra
LOCAL_SRC_FILES := ../../../common/gl_api.c jni_wrapper.c
LOCAL_LDLIBS := -lGLESv2

include $(BUILD_SHARED_LIBRARY)
