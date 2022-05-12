#ifndef IPLUGIN_H_
#define IPLUGIN_H_

#define PLUGIN_EXPORTS

#ifdef PLUGIN_EXPORTS
#define PLUGINDECL __declspec(dllexport)
#else
#define PLUGINDECL __declspec(dllimport)
#endif

#include <string>
using namespace std;

class PluginManager;

class IPlugin
{
public:
	virtual ~IPlugin() { }

	virtual bool Init() {};
	virtual bool Update() {};
	virtual bool Render() {};
	virtual bool End() {};
	virtual const std::string GetName() {};
};

typedef IPlugin* (*CREATEPLUGIN)(PluginManager& mgr);


extern "C" PLUGINDECL IPlugin* CreatePlugin(PluginManager & mgr);



#endif