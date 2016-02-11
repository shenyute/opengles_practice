LOCAL_PATH := $(call my-dir)
PROJECT_ROOT_PATH := $(LOCAL_PATH)/../../../
CORE_RELATIVE_PATH := ../../../common/
 
include $(CLEAR_VARS)
 
LOCAL_MODULE    := gl_api
LOCAL_CFLAGS    := -Wall -Wextra
LOCAL_SRC_FILES := platform_asset_utils.c \
                   platform_log.c \
                   renderer_wrapper.c \
                   $(CORE_RELATIVE_PATH)/asset_utils.c \
                   $(CORE_RELATIVE_PATH)/buffer.c \
                   $(CORE_RELATIVE_PATH)/gl_api.cpp \
                   $(CORE_RELATIVE_PATH)/image.c \
                   $(CORE_RELATIVE_PATH)/shader.c \
                   $(CORE_RELATIVE_PATH)/texture.c \
                   $(CORE_RELATIVE_PATH)/emitter_shader.cpp \
                   $(CORE_RELATIVE_PATH)/emitter_object.cpp \

LOCAL_C_INCLUDES := $(PROJECT_ROOT_PATH)/common/
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/third_party/
#LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/core/
LOCAL_STATIC_LIBRARIES := libpng
LOCAL_LDLIBS := -lGLESv2 -llog -landroid -lm
 
include $(BUILD_SHARED_LIBRARY)
 
$(call import-add-path,$(PROJECT_ROOT_PATH)/third_party)
$(call import-module,libpng)
