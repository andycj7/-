#include <HelloPlugin.h>
#include <sstream>
#include <stdio.h>

using namespace std;

//在atelier_plugin命名空间中实现js调用的具体方法
namespace atelier_plugin {

//实例化HelloPlugin对象
AtelierPlugin* CreateHelloPlugin() {
  return new HelloPlugin();
}

//实现空的HelloPlugin方法
HelloPlugin::~HelloPlugin() {
}

//实现Initialize方法
void HelloPlugin::Initialize() {
  logAtelier("HelloPlugin::Initialized !!!");	//打印日志
}

//实现Execute方法
void HelloPlugin::Execute(std::string action, std::string callback_id, std::string args) {
  logAtelier("HelloPlugin::Execute !!!  action: %s",action.c_str());	//打印日志
  //对JS端的Start方法调用PostMsgToJs方法
  if (action == "Start") {
    logAtelier("HelloPlugin::Execute Start PostMsgToJs message:%s.", args.c_str());	//打印日志
    PostMsgToJs(callback_id, true, 1, "Hello Emss!", false);	//根据callback_id将Hello Emss字符串传递给JS端
  }
}

}//namespace atelier_plugin
