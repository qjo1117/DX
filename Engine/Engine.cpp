﻿#include "pch.h"
#include "Engine.h"
#include "Box.h"
#include "Camera.h"



int32 Engine::Init(HWND hWnd, HINSTANCE hInstance)
{


	m_info.hWnd = hWnd;
	m_info.hInst = hInstance;

	ResizeWindow(800, 480);
	SetWindowTitle(L"겜플3A_박정욱_17032032");

	/* ------ Mgr Init ----- */
	if (GET_SINGLE(Device)->Init(hWnd) == false) {
		ASSERT_CRASH("Not Create Device");
	}

	GET_SINGLE(Timer)->Init(hWnd);
	GET_SINGLE(Input)->Init(hWnd);
#ifdef DEF_EDITOR
	GET_SINGLE(EditorManager)->Init(hWnd);
#endif

	DEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);



	return 0;
}

int32 Engine::Update()
{
	GET_SINGLE(Timer)->Update();
	GET_SINGLE(Input)->Update();
	GET_SINGLE(SceneManager)->Update();

#ifdef DEF_EDITOR
	GET_SINGLE(EditorManager)->Update();
#endif

	return 0;
}

int32 Engine::Render()
{
	DEVICE->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, m_info.color, 1.0f, 0);

	{
		DEVICE->BeginScene();

		GET_SINGLE(SceneManager)->Render();
#ifdef DEF_EDITOR
		GET_SINGLE(EditorManager)->Render();
#endif
		DEVICE->EndScene();
	}

	DEVICE->Present(nullptr, nullptr, nullptr, nullptr);

	return 0;
}

int32 Engine::End()
{
	GET_SINGLE(EditorManager)->End();
#ifdef DEF_EDITOR
	GET_SINGLE(SceneManager)->End();
#endif
	GET_SINGLE(Device)->End();


	return 0;
}


void Engine::ResizeWindow(int32 width, int32 height)
{
	m_info.width = width;
	m_info.height = height;

	RECT rect = { 0, 0, width, height };
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(m_info.hWnd, 0, 100, 100, rect.right - rect.left, rect.bottom - rect.top, 0);
}

void Engine::SetWindowTitle(const wstring& title)
{
	m_info.title = title;
	::SetWindowTextW(m_info.hWnd, m_info.title.c_str());
}
