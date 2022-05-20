#include "pch.h"
#include "EditorManager.h"
#include "Engine.h"

#include "DirectoryEditor.h"
#include "MenuEditor.h"
#include "SceneObjectEditor.h"


void EditorManager::Init(HWND hWnd)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();


    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX9_Init(DEVICE);

    m_hWnd = hWnd;


}

void EditorManager::Update()
{
    //  Start the Dear ImGui frame
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();


    ImGui::NewFrame();
    
    // Base Editor
    {
        MainMenuBar();
        ConsoleEditor();
    }
    for (auto& item : m_vecEditor) {
        item.second->ShowEditor();
    }

    ImGui::EndFrame();
}

void EditorManager::Render()
{
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void EditorManager::End()
{
    for (auto& log : m_arrLogs) {
        log.clear();
    }
    Recursion_MenuBarClear(m_pMenuBar);
    m_pMenuBar = nullptr;

    for (auto& item : m_vecEditor) {
        if (item.second != nullptr) {
            item.second->End();
            SAFEDELETE(item.second);
        }
    }
    m_vecEditor.clear();


    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void EditorManager::RegisterEditor(function<void(void)> p_editor)
{
    //Ref<IEditor> 
    //vecEditor.push_back();
}

void EditorManager::MainMenuBar()
{
    if (ImGui::BeginMainMenuBar()) {
        Recursion_MenuPresent(m_pMenuBar);
        ImGui::EndMainMenuBar();
    }
}

void EditorManager::Recursion_MenuPresent(Ref<MenuInfo>& p_info)
{
    for (Ref<MenuInfo> info : p_info->vecChildMenu) {
        if (info->IsMenuBar()) {
            if (ImGui::BeginMenu(info->strTitle.c_str())) {
                Recursion_MenuPresent(info);
                ImGui::EndMenu();
            }
        }
        else {
            if (ImGui::MenuItem(info->strTitle.c_str())) {
                // TODO : GetWindow를 구현하자
                info->FuncOn();
            }
        }
    }
}

void EditorManager::Recursion_MenuBarClear(Ref<MenuInfo> p_pInfo)
{
    if (p_pInfo->vecChildMenu.empty()) {
        p_pInfo->FuncOn = nullptr;
        p_pInfo = nullptr;
        return;
    }

    for (Ref<MenuInfo>& info : p_pInfo->vecChildMenu) {
        Recursion_MenuBarClear(info);
        info->FuncOn = nullptr;
        info = nullptr;

    }
    p_pInfo = nullptr;
}

void EditorManager::RegisterMenuBar(const string& p_title, function<void(void)> p_func)
{
    // 경로를 vector로 받아둔다.
    vector<string> titleToken = Utils::Split(p_title, '/');

    Ref<MenuInfo> ret = Recursion_FindMenuBar(m_pMenuBar, titleToken);
    ret->FuncOn = p_func;
}

Ref<MenuInfo> EditorManager::Recursion_FindMenuBar(Ref<MenuInfo>& p_info, const vector<string>& title, int32 index)
{
    // 찾은경우
    if (title.size() == index) {
        return p_info;
    }
    else if (p_info == nullptr) {
        // 없는 경우
        Ref<MenuInfo> ret = make_shared<MenuInfo>();
        ret->strTitle = title[index];
        p_info = ret;
        return Recursion_FindMenuBar(ret, title, ++index);
    }

    // 순회하는 경우
    for (auto& info : p_info->vecChildMenu) {
        if (title[index] == info->strTitle) {
            return Recursion_FindMenuBar(info, title, ++index);
        }
    }

    // 없는 경우
    Ref<MenuInfo> ret = make_shared<MenuInfo>();
    ret->strTitle = title[index];
    p_info->vecChildMenu.push_back(ret);
    return Recursion_FindMenuBar(ret, title, ++index);
}

void EditorManager::ConsoleEditor()
{
    ImGui::Begin("Console");

    if (LOG_STATE::LOG & m_eState) {
        for (string& log : m_arrLogs[0]) {
            string text = "| Log | " + log;
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), text.c_str());
        }
        ImGui::Separator();
    }
    if (LOG_STATE::WARNING & m_eState) {
        for (string& log : m_arrLogs[1]) {
            string text = "| Warning | " + log;
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), text.c_str());
        }
        ImGui::Separator();
    }
    if (LOG_STATE::ERROR_ & m_eState) {
        for (string& log : m_arrLogs[2]) {
            string text = "| Error | " + log;
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), text.c_str());
        }
        ImGui::Separator();
    }
    
    ImGui::End();
}

void EditorManager::Log(const string& log, uint8 state)
{
    if (LOG_STATE::LOG & state) {
        m_arrLogs[0].push_back(log);
    }
    if (LOG_STATE::WARNING & state) {
        m_arrLogs[1].push_back(log);
    }
    if (LOG_STATE::ERROR_ & state) {
        m_arrLogs[2].push_back(log);
    }
}

void EditorManager::Clear(uint8 state)
{
    if (LOG_STATE::LOG & m_eState) {
        m_arrLogs[0].clear();
    }
    if (LOG_STATE::WARNING & m_eState) {
        m_arrLogs[1].clear();
    }
    if (LOG_STATE::ERROR_ & m_eState) {
        m_arrLogs[2].clear();
    }
}

void EditorManager::PushEditor(const string& name, IEditor* editor)
{
    if (m_vecEditor[name]) {
        return;
    }

    m_vecEditor[name] = editor;
}
