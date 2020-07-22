#include "file_system_plugin.h"
#include <stdio.h>
#include <unistd.h> //包含许多系统服务的函数原型
#include <fstream>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

//#include <atelier_plugin/atelier_plugin_common.h>

using namespace std;

//实现js调用的具体方法
namespace base_plugin {

BasePlugin* CreateFileSystemPlugin() {
  	return new FileSystemPlugin();
}

FileSystemPlugin::FileSystemPlugin() {

	char *current_path = getcwd(NULL, 0);
	file_operation_ = new FileOperation(current_path);
	delete [] current_path;
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
		vector<string> file_list = file_operation_->GetFileList();
		for(size_t i = 2; i < file_list.size(); i++){
			//前两个为当前目录，和上一级目录
			writer.String(file_list[i].c_str());
		}
		writer.EndArray();
		PostMessage(callback_id, true, BASEPLUGIN_MAGIC_NUM, s.GetString(), false);
	} else if (action == "openFileOrFolderByName") {
		//通过文件名打开当前文件夹下的文件或文件夹
		char *content = file_operation_->OpenFileOrFolderByName(args.c_str());
		if(content == NULL){
			//格式['folder,<file_names>']
			writer.String("folder");
			writer.String(file_operation_->GetRootPath());
			vector<string> file_list = file_operation_->GetFileList();
			for(size_t i = 2; i < file_list.size(); i++){
				writer.String(file_list[i].c_str());
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
			//格式['folder,<file_names>']
			writer.String("folder");
			writer.String(file_operation_->GetRootPath());
			vector<string> file_list = file_operation_->GetFileList();
			for(size_t i = 2; i < file_list.size(); i++){
				writer.String(file_list[i].c_str());
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
		vector<string> file_list = file_operation_->GetFileList();
		for(size_t i = 2; i < file_list.size(); i++){
			//前两个为当前目录，和上一级目录
			writer.String(file_list[i].c_str());
		}
		writer.EndArray();
		PostMessage(callback_id, true, BASEPLUGIN_MAGIC_NUM, s.GetString(), false);
	} else if (action == "searchFileOrFolderByName") {

		vector<string> search_result;
		file_operation_->SearchFileOrFolderByName(args.c_str(), file_operation_->GetRootPath(), search_result);
		for(size_t i = 0; i < search_result.size(); i++){
			writer.String(search_result[i].c_str());
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
