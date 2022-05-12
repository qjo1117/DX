#pragma once

class IPlugin;

struct PluginInfo
{
	IPlugin* pPlugin = nullptr;
	HMODULE hDll = nullptr;
};

class PluginManager
{
	DECLARE_SINGLE(PluginManager);
public:
	void Init();
	void Update();
	void Render();
	void End();

	void LoadPlugins();  
	bool LoadPlugin(const wstring& p_fileName);

public:
	
private:
	PRIVATE_PROPERTY(vector<PluginInfo>, vecPlugins);
};
