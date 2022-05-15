#pragma once


#include "../Engine/IPlugin.h"
#include "../Editor/EditorManager.h"

class PluginAction :
    public IPlugin
{
public:
    PluginAction() : m_strName("PluginAction") {}

    virtual bool Init() override;
    virtual bool Update() override;
    virtual bool Render() override;
    virtual bool ShutDown() { return true; }
    virtual const std::string GetName() { return m_strName; };

public:
    string m_strName;
    inline static PluginAction* m_pInstance = nullptr;
};

CREATE_PLUGIN(PluginAction)