#pragma once


#include "../Engine/IPlugin.h"




class PluginAction :
    public IPlugin
{
public:
    PluginAction(PluginManager& manager) : m_strName("PluginAction") { m_pManager = &manager; }

    virtual bool Init() override;
    virtual bool Update() override;
    virtual bool Render() override;
    virtual bool End() override;
    virtual bool ShutDown() { return true; }
    virtual const std::string& GetName() { return m_strName; };

public:
    string m_strName;
    inline static PluginManager* m_pManager = nullptr;
};

CREATE_PLUGIN(PluginAction)