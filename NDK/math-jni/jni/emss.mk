LOCAL_PATH := $(call my-dir)
			
########module 1 #########
include $(CLEAR_VARS)

LOCAL_MODULE := Math    #模块名

LOCAL_SRC_FILES := MathFunctions.cpp    #源文件名

include $(BUILD_SHARED_LIBRARY)    #编译生成动态库