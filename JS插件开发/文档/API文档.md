# 接口文档 #

## init ##
### 简要描述：###
- 打开默认路径

### 参数 ###
参数名|必选|类型|说明
:--:|:--:|:--:|:--:
call_back|是|function|回调函数               

### 回调函数示例 ###
    function call_back(){
		//接收参数的格式
		//<err>,<root_path>,<folder_num>,<folder_names>,<file_num>,<file_names>
		//处理接口返回的参数
	}

### 回调函数接收参数 ###

参数名|类型|说明
:--:|:--:|:--:
err|object|关于接口调用错误的信息
folder_num|number|获取的文件夹的个数
folder_name|string|获取的文件夹的名称
file_num|number|获取的文件的个数
file_name|string|获取文件的名称

## openFileOrFolderByName ##
### 简要描述：###
- 通过文件名，打开当前目录下的文件夹或文件

### 参数 ###
参数名|必选|类型|说明
:--:|:--:|:--:|:--:
name|是|string|文件名
call_back|是|function|回调函数               

### 回调函数示例 ###
    function call_back(){
		//接收参数的格式
		//<err>,<type:folder>,<root_path>,<folder_num>,<folder_names>,<file_num>,<file_names>
		//<err>,<type:file>,<content>
		//处理接口返回的参数
	}

### 回调函数接收参数 ###

参数名|类型|说明
:--:|:--:|:--:
err|object|关于接口调用错误的信息
type|string|folder表示打开的是文件夹，file表示打开的是文件
root_path|string|当前文件夹路径
folder_num|number|获取的文件夹的个数
folder_name|string|获取的文件夹的名称
file_num|number|获取的文件的个数
file_name|string|获取文件的名称
content|string|文件中的txt格式的内容

## openFileOrFolderByPath ##

### 简要描述：###
- 通过文件路径，打开当前目录下的文件夹或文件

### 参数 ###
参数名|必选|类型|说明
:--:|:--:|:--:|:--:
path|是|string|文件路径
call_back|是|function|回调函数               

### 回调函数示例 ###
    function call_back(){
		//接收参数的格式
		//<err>,<type:folder>,<folder_num>,<folder_names>,<file_num>,<file_names>
		//<err>,<type:file>,<content>
		//处理接口返回的参数
	}

### 回调函数接收参数 ###

参数名|类型|说明
:--:|:--:|:--:
err|object|关于接口调用错误的信息
type|string|folder表示打开的是文件夹，file表示打开的是文件
folder_num|number|获取的文件夹的个数
folder_name|string|获取的文件夹的名称
file_num|number|获取的文件的个数
file_name|string|获取文件的名称
content|string|文件中的txt格式的内容

## returnPreFolder ##

### 简要描述：###
- 返回当前目录的上一级目录

### 参数 ###
参数名|必选|类型|说明
:--:|:--:|:--:|:--:
call_back|是|function|回调函数               

### 回调函数示例 ###
    function call_back(){
		//接收参数的格式
		//<err>,<root_path>,<folder_num>,<folder_names>,<file_num>,<file_names>
		//处理接口返回的参数
	}

### 回调函数接收参数 ###

参数名|类型|说明
:--:|:--:|:--:
err|object|关于接口调用错误的信息
root_path|string|当前文件夹路径
folder_num|number|获取的文件夹的个数
folder_name|string|获取的文件夹的名称
file_num|number|获取的文件的个数
file_name|string|获取文件的名称

## searchFileOrFolderByName ##

### 简要描述：###
- 搜索当前目录和下级目录内的同名文件

### 参数 ###
参数名|必选|类型|说明
:--:|:--:|:--:|:--:
name|是|string|文件名
call_back|是|function|回调函数               

### 回调函数示例 ###
    function call_back(){
		//接收参数的格式
		//<err>,<search_result>
		//处理接口返回的参数
	}

### 回调函数接收参数 ###

参数名|类型|说明
:--:|:--:|:--:
err|object|关于接口调用错误的信息
search_result|string|搜索结果