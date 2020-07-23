#include "file_system_plugin.h"
#include <stdio.h>
#include <unistd.h> //包含许多系统服务的函数原型
#include <fstream>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <atelier_plugin/atelier_plugin_common.h>

using namespace std;

//实现js调用的具体方法
namespace base_plugin {

BasePlugin* CreateFileSystemPlugin() {
  	return new FileSystemPlugin();
}

FileSystemPlugin::FileSystemPlugin() {

	file_operation_ = new FileOperation("/sdcard");
}

FileSystemPlugin::~FileSystemPlugin() {
	delete file_operation_;
}

//实现Initialize方法
void FileSystemPlugin::Init() {

	
}

//实现Execute方法
void FileSystemPlugin::OnMessage(std::string action, std::string callback_id, std::string args) {

	rapidjson::StringBuffer s;
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	writer.StartArray();
	if(action == "init"){
		//初始化，返回app所在文件加路径和文件列表
		writer.String(file_operation_->GetRootPath());
		//格式['<root_path_>,<foler_num>,<folder_name>,<file_num>,<filer_names>']
		//写入目录中文件夹的个数和文件夹名
		vector<string> temp_list = file_operation_->GetFolderList();
		writer.Uint(temp_list.size());
		for(size_t i = 0; i < temp_list.size(); i++){
			writer.String(temp_list[i].c_str());
		}
		//写入目录中文件的个数和文件名
		temp_list = file_operation_->GetFileList();
		writer.Uint(temp_list.size());
		for(size_t i = 0; i < temp_list.size(); i++){
			writer.String(temp_list[i].c_str());
		}
		writer.EndArray();
		PostMessage(callback_id, true, BASEPLUGIN_MAGIC_NUM, s.GetString(), false);
	} else if (action == "openFileOrFolderByName") {
		//通过文件名打开当前文件夹下的文件或文件夹
		char *content = file_operation_->OpenFileOrFolderByName(args.c_str());
		if(content == NULL){
			//格式['folder,<root_path_>,<foler_num>,<folder_name>,<file_num>,<filer_names>']
			writer.String("folder");
			writer.String(file_operation_->GetRootPath());
			//写入目录中文件夹的个数和文件夹名
			vector<string> temp_list = file_operation_->GetFolderList();
			writer.Uint(temp_list.size());
			for(size_t i = 0; i < temp_list.size(); i++){
				writer.String(temp_list[i].c_str());
			}
			//写入目录中文件的个数和文件名
			temp_list = file_operation_->GetFileList();
			writer.Uint(temp_list.size());
			for(size_t i = 0; i < temp_list.size(); i++){
				writer.String(temp_list[i].c_str());
			}
			writer.EndArray();
			PostMessage(callback_id, true, BASEPLUGIN_MAGIC_NUM, s.GetString(), false);
		} else {
			//格式['file,<file_name>']
			writer.String("file");
			writer.String(content);
			writer.EndArray();
			PostMessage(callback_id, true, BASEPLUGIN_MAGIC_NUM, s.GetString(), false);
		}		
	} else if (action == "openFileOrFolderByPath") {
		//通过文件名打开当前文件夹下的文件或文件夹
		char *content = file_operation_->OpenFileOrFolderByPath(args.c_str());
		if(content == NULL){
			//格式['folder,<root_path_>,<foler_num>,<folder_name>,<file_num>,<filer_names>']
			writer.String("folder");
			writer.String(file_operation_->GetRootPath());
			//写入目录中文件夹的个数和文件夹名
			vector<string> temp_list = file_operation_->GetFolderList();
			writer.Uint(temp_list.size());
			for(size_t i = 0; i < temp_list.size(); i++){
				writer.String(temp_list[i].c_str());
			}
			//写入目录中文件的个数和文件名
			temp_list = file_operation_->GetFileList();
			writer.Uint(temp_list.size());
			for(size_t i = 0; i < temp_list.size(); i++){
				writer.String(temp_list[i].c_str());
			}
			writer.EndArray();
			PostMessage(callback_id, true, BASEPLUGIN_MAGIC_NUM, s.GetString(), false);
		} else {
			//格式['file,<file_name>']
			writer.String("file");
			writer.String(content);
			writer.EndArray();
			PostMessage(callback_id, true, BASEPLUGIN_MAGIC_NUM, s.GetString(), false);
		}		
	} else if (action == "returnPreFolder") {
		//返回上一级文件夹
		file_operation_->ReturnPreFolder();
		writer.String(file_operation_->GetRootPath());
		//格式['<root_path_>,<foler_num>,<folder_name>,<file_num>,<filer_names>']
		//写入目录中文件夹的个数和文件夹名
		vector<string> temp_list = file_operation_->GetFolderList();
		writer.Uint(temp_list.size());
		for(size_t i = 0; i < temp_list.size(); i++){
			writer.String(temp_list[i].c_str());
		}
		//写入目录中文件的个数和文件名
		temp_list = file_operation_->GetFileList();
		writer.Uint(temp_list.size());
		for(size_t i = 0; i < temp_list.size(); i++){
			writer.String(temp_list[i].c_str());
		}
		writer.EndArray();
		PostMessage(callback_id, true, BASEPLUGIN_MAGIC_NUM, s.GetString(), false);
	} else if (action == "searchFileOrFolderByName") {

		//格式['<file_num>,<file_names>,<folder_num>,<folder_names>']
		vector<string> file_result, folder_result;
		file_operation_->SearchFileOrFolderByName(args.c_str(), file_operation_->GetRootPath(), file_result, folder_result);
		writer.Uint(file_result.size());
		for(size_t i = 0; i < file_result.size(); i++){
			writer.String(file_result[i].c_str());
		}
		writer.Uint(folder_result.size());
		for(size_t i = 0; i < folder_result.size(); i++){
			writer.String(folder_result[i].c_str());
		}
		writer.EndArray();
		PostMessage(callback_id, true, BASEPLUGIN_MAGIC_NUM, s.GetString(), false);
	} else {
		PostMessage(callback_id, false, BASEPLUGIN_MAGIC_NUM, "no such emss", false);
	}
}

std::string FileSystemPlugin :: GetPluginVersion(){
	
}
std::string FileSystemPlugin :: GetPluginBuildTime(){
	
}

}//namespace atelier_plugin
