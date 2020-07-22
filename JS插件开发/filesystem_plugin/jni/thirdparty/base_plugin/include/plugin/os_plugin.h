/**
 * @file os_plugin.h
 * Copyright 2017 <IECAS>
 */
#ifndef BASEPLUGIN_OS_PLUGIN_H_
#define BASEPLUGIN_OS_PLUGIN_H_

#include <atelier_plugin/atelier_plugin.h>
#include <string>

// v2.0.0版本的兼容性处理
#define BASEPLUGIN_MAGIN_NUM 999999
namespace base_plugin
{
    void _PostMessage(std::string callback_id, bool success, long status, std::string result, bool keep_callback);

    class OSPlugin : public atelier_plugin::AtelierPlugin
    {
      public:
        virtual void Init() = 0;
        virtual void OnMessage(std::string action, std::string callback_id, std::string args) = 0;

        void Initialize();
        void Execute(std::string action, std::string callback_id, std::string args);
    };
}
#endif // BASEPLUGIN_OS_PLUGIN_H_
