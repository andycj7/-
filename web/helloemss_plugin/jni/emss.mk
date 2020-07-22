LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := HelloEmss	#模块名

LOCAL_SRC_FILES := HelloPlugin.cpp	#源文件名

LOCAL_LDLIBS :=	-llog \
				-latelier_plugin \
				-lc++
#-llog表示连接log库
#-latelier_plugig表示连接atelier_plugin库
#-lc++表示连接c++库

include $(BUILD_SHARED_LIBRARY)
