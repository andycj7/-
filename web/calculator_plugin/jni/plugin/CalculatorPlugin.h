//添加宏定义HELLO_PLUGIN
#ifndef CALCULATOR_PLUGIN
#define CALCULATOR_PLUGIN

#include <plugin/base_plugin.h>
#include <string>

//使用namespace atelier_plugin
namespace base_plugin {

//使用extern "C"中创建CreateHelloPlugin方法
#ifdef __cplusplus
extern "C" {
#endif
  __attribute__ ((visibility("default"))) BasePlugin* CreateCalculatorPlugin();
#ifdef __cplusplus
}
#endif

//创建HelloPlugin类继承AtelierPlugin
class CalculatorPlugin : public BasePlugin {
 public:
  CalculatorPlugin() { }
  virtual ~CalculatorPlugin();
  
  //声明Initialize方法
  virtual void Init();
  //声明Execute方法
  virtual void OnMessage(std::string action, std::string callback_id,std::string args);
  virtual std::string GetPluginVersion();
  virtual std::string GetPluginBuildTime();
};

}
#endif
