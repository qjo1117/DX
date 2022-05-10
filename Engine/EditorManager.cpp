#include "pch.h"
#include "EditorManager.h"
#include "Engine.h"

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
    ImGui::StyleColorsClassic();


    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX9_Init(DEVICE);

    m_hWnd = hWnd;

    AddEditor([]() { EDITOR->ConsoleEditor(); });
}

void EditorManager::Update()
{
    //  Start the Dear ImGui frame
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();


    ImGui::NewFrame();

    for (function<void(void)> editor : m_vecEditor) {
        editor();
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
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void EditorManager::AddEditor(function<void(void)> p_editor)
{
    m_vecEditor.push_back(p_editor);
}

void EditorManager::ConsoleEditor()
{
    ImGui::Begin(u8"Console");

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
