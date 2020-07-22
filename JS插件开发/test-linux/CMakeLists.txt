cmake_minimum_required(VERSION 3.2) #指定运行此配置文件所需的CMake的最低版本

set(PROJECT_NAME FileOperation) #设置项目名称变量
project(${PROJECT_NAME})#设置项目名称
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11") #在编译C++代码时加上C++11支持选项
set(INC_DIR ./thirdparty) 
INCLUDE_DIRECTORIES(${INC_DIR})#设置第三方库头文件路径
set(LIB_DIR ./output)          
LINK_DIRECTORIES(${LIB_DIR}) #设置依赖库的路径


#aux_source_directory(./thirdparty DIR_SRCS) #用于查找指定目录下的所有源文件，将结果存进指定变量，相当于8-9两行的功能
file(GLOB cpp_src_file "*.cpp") #查找当前文件夹中所有.cpp结尾的源代码文件
set(DIR_SRCS ${cpp_src_file}) #将找到的所有文件设置为一个变量

#ADD_LIBRARY(${PROJECT_NAME} ${DIR_SRCS}) #将源文件编译成一个静态库
#ADD_LIBRARY(${PROJECT_NAME} SHARED ${DIR_SRCS}) #将源文件编译成一个动态库
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/) #设置库文件输出的指定目录

add_executable(${PROJECT_NAME} ${DIR_SRCS}) #将源文件编译成可执行文件
target_link_libraries(${PROJECT_NAME} libFileOperation.a) #链接静态库
#target_link_libraries(${PROJECT_NAME} libMyMath.dll) #链接动态库
set(EXECUTABLE_OUTPUT_PATH ../output) #指定生成的可执行文件所放的路径