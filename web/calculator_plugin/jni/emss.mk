LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := prebuilt-baseplugin
LOCAL_SRC_FILES := \
		thirdparty/base_plugin/lib/libbase_plugin.so
LOCAL_EXPORT_C_INCLUDES := \
		thirdparty/base_plugin/include \
		thirdparty
LOCAL_EXPORT_LDFLAGS := -llog -lc++
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := CalculatorPlugin#模块名

LOCAL_SRC_FILES := plugin/CalculatorPlugin.cpp	#源文件名
LOCAL_SHARED_LIBRARIES := prebuilt-baseplugin

include $(BUILD_SHARED_LIBRARY)
