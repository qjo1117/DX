#include "pch.h"
#include "PluginAction.h"

bool PluginAction::Init()
{
    int32 size = 0;

    

    return true;
}

bool PluginAction::Update()
{
    return false;
}

bool PluginAction::Render()
{
    return false;
}

bool PluginAction::End()
{
    return false;
}

PLUGINDECL IPlugin* CreatePlugin(PluginManager& mgr)
{
    return new PluginAction(mgr);
}
