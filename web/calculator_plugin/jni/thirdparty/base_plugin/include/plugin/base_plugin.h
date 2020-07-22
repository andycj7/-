/**
 * @file base_plugin.h
 * Copyright 2017 <IECAS>
 */
#ifndef BASEPLUGIN_BASE_PLUGIN_H_
#define BASEPLUGIN_BASE_PLUGIN_H_

#include <plugin/os_plugin.h>

#define BASEPLUGIN_VERSION "2.0.1"
#define BASEPLUGIN_MAGIC_NUM 999999

namespace base_plugin
{
void PostMessage(std::string callback_id, bool success, long status, std::string result, bool keep_callback);

class BasePlugin : public OSPlugin
{
public:
  virtual void Init() = 0;
  virtual void OnMessage(std::string action, std::string callback_id, std::string args) = 0;
  virtual std::string GetPluginVersion() = 0;
  virtual std::string GetPluginBuildTime() = 0;
};
} // namespace base_plugin
#endif // BASEPLUGIN_BASE_PLUGIN_H_
