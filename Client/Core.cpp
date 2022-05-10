#include "pch.h"
#include "Core.h"
#include "StartScene.h"

bool Core::loop = true;

void Core::Init()
{
    Engine::GetI()->Init(m_hWnd, m_hInst);

    GET_SINGLE(SceneManager)->CreateScene<StartScene>(SCENE_TYPE::START);

    GET_SINGLE(SceneManager)->LoadScene(SCENE_TYPE::START);
}

void Core::Update()
{
    GET_SINGLE(Engine)->Update();

    if (Input::GetI()->KeyDown("Right")) {
        int32 a = 10;
    }

    GET_SINGLE(Timer)->ShowFpsWindowTitle();
}

void Core::Render()
{
    GET_SINGLE(Engine)->Render();
}

void Core::End()
{
    GET_SINGLE(Engine)->End();
}

int Core::Run(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    Init();

    while (Core::loop) {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT) {
                return 0;
            }
        }
        else {
            Update();
            Render();
        }
    }

    End();

    return (int)msg.wParam;
}



ATOM Core::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, 0);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = m_strTitle.c_str();
    wcex.hIconSm = LoadIcon(wcex.hInstance, 0);

    return RegisterClassExW(&wcex);
}

BOOL Core::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    m_hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    m_hWnd = CreateWindowW(m_strTitle.c_str(), m_strTitle.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!m_hWnd)
    {
        return FALSE;
    }

    ShowWindow(m_hWnd, nCmdShow);
    UpdateWindow(m_hWnd);

    return TRUE;
}

LRESULT CALLBACK Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) {
        return true;
    }

    switch (message) {
    case WM_DESTROY:
        Core::loop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}