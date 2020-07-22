#include "CalculatorPlugin.h"
#include <stdio.h>

using namespace std;

//在atelier_plugin命名空间中实现js调用的具体方法
namespace base_plugin {

//实例化HelloPlugin对象
BasePlugin* CreateCalculatorPlugin() {
  return new CalculatorPlugin();
}

//实现空的HelloPlugin方法
CalculatorPlugin::~CalculatorPlugin() {
}

//实现Initialize方法
void CalculatorPlugin::Init() {
}

//实现Execute方法
void CalculatorPlugin::OnMessage(std::string action, std::string callback_id, std::string args) {
  //对JS端的Start方法调用PostMsgToJs方法
  if (action == "Start") {
    PostMessage(callback_id, true, 1, "Hello Emss!", false);
  }
}

std::string CalculatorPlugin :: GetPluginVersion(){
	
}
std::string CalculatorPlugin :: GetPluginBuildTime(){
	
}

}//namespace atelier_plugin
