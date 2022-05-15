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

	virtual bool Init() { return false; }
	virtual bool Update() { return false; }
	virtual bool Render() { return false; }
	virtual bool End() { return false; }
	virtual const std::string GetName() { return "IPlugin"; }
};

typedef IPlugin* (*CREATEPLUGIN)();

#define CREATE_PLUGIN(Plugin)						\
extern "C" PLUGINDECL IPlugin * CreatePlugin()		\
{													\
	return new Plugin();							\
}												  


#endif