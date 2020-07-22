//添加宏定义HELLO_PLUGIN
#ifndef HELLO_PLUGIN
#define HELLO_PLUGIN

#include <atelier_plugin/atelier_plugin.h>
#include <string>

//使用namespace atelier_plugin
namespace atelier_plugin {

//使用extern "C"中创建CreateHelloPlugin方法
#ifdef __cplusplus
extern "C" {
#endif
  __attribute__ ((visibility("default"))) AtelierPlugin* CreateHelloPlugin();
#ifdef __cplusplus
}
#endif

//创建HelloPlugin类继承AtelierPlugin
class HelloPlugin : public AtelierPlugin {
 public:
  HelloPlugin() { }
  virtual ~HelloPlugin();
  
  //声明Initialize方法
  virtual void Initialize();
  //声明Execute方法
  virtual void Execute(std::string action, std::string callback_id,
                       std::string args);
};

}
#endif
