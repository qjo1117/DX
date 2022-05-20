#include "pch.h"
#include "PluginAction.h"


bool PluginAction::Init()
{
    IPlugin::Init();
    

    /*m_pManager->Log("HelloDLL");*/

    m_pManager->GetEditor()->Log("HelloDLL");

    return true;
}

bool PluginAction::Update()
{

    //EDITOR->Log("PluginAction Update");


    
    return true;
}

bool PluginAction::Render()
{



    
    return true;
}

bool PluginAction::End()
{

    return true;
}

