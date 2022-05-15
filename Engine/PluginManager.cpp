#include "pch.h"
#include "PluginManager.h"
#include "DirectoryManager.h"
#include "IPlugin.h"

void PluginManager::Init()
{
    LoadPlugins();
    for (auto& info : vecPlugins) {
        info.pPlugin->Init();
    }
}

void PluginManager::Update()
{
    for (auto& info : vecPlugins) {
        info.pPlugin->Update();
    }
}

void PluginManager::Render()
{
    for (auto& info : vecPlugins) {
        info.pPlugin->Render();
    }
}

void PluginManager::End()
{
    for (auto& info : vecPlugins) {
        info.pPlugin->End();
        SAFEDELETE(info.pPlugin);
    }
}

void PluginManager::LoadPlugins()
{
	vector<Ref<FileInfo>> vecFileInfos;
	GET_SINGLE(DirectoryManager)->FindFileInfo(GET_SINGLE(DirectoryManager)->GetFileInfo(), vecFileInfos, ".dll");

    string rootPath = GET_SINGLE(DirectoryManager)->GetFileInfo()->PathInfo.string();
    for (Ref<FileInfo>& fileInfo : vecFileInfos) {
        wstring fullPath = Utils::Str2Wstr(rootPath + "Output\\" + fileInfo->Name);
        LoadPlugin(fullPath);
    }
}

bool PluginManager::LoadPlugin(const wstring& p_fileName)
{
    HMODULE hDll = ::LoadLibraryW(p_fileName.c_str());
    if (hDll == NULL) {
        LPVOID lpMsgBuf;
        ::FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
            (LPTSTR)&lpMsgBuf,
            0,
            NULL
        );

        ::OutputDebugStringA((char*)lpMsgBuf);

        LocalFree(lpMsgBuf);
        return false;
    }

    CREATEPLUGIN pFunc = (CREATEPLUGIN)::GetProcAddress(hDll, "CreatePlugin");
    if (pFunc == nullptr) {
        return false;
    }

    IPlugin* pPlugin = pFunc();
    if (pPlugin == nullptr) {
        return false;
    }

    PluginInfo info;
    info.pPlugin = pPlugin;
    info.hDll = hDll;

    m_vecPlugins.push_back(info);

    return true;
}
