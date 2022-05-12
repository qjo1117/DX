#pragma once

#include "../Engine/IPlugin.h"

class PluginAction :
    public IPlugin
{
public:
    PluginAction(PluginManager& manager) : m_hManager(manager), m_strName("PluginAction") {}

    virtual bool Init() override;
    virtual bool Update() override;
    virtual bool Render() override;
    virtual bool End() override;
    virtual bool ShutDown() { return true; }
    virtual const std::string GetName() { return m_strName; };

public:
    PluginManager& m_hManager;
    string m_strName;
};
