//添加宏定义HELLO_PLUGIN
#ifndef FILE_SYSTEM_PLUGIN
#define FILE_SYSTEM_PLUGIN

#include <plugin/base_plugin.h>
#include <string>
#include "file_operation.h"

//使用namespace base_plugin
namespace base_plugin {

//使用extern "C"中创建Createxxx方法
#ifdef __cplusplus
extern "C" {
#endif
  __attribute__ ((visibility("default"))) BasePlugin* CreateFileSystemPlugin();
#ifdef __cplusplus
}
#endif

class FileSystemPlugin : public BasePlugin {
public:
	FileSystemPlugin();
	virtual ~FileSystemPlugin();
  
	virtual void Init();

	virtual void OnMessage(std::string action, std::string callback_id,std::string args);
	virtual std::string GetPluginVersion();
	virtual std::string GetPluginBuildTime();
  
private:
	FileOperation *file_operation_;
};

}
#endif
