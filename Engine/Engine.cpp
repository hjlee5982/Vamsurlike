#include "pch.h"
#include "Engine.h"
#include "Scene.h"
#include "RenderManager.h"
#include "AssetManager.h"
#include "CollisionManager.h"
#include "Log.h"
#include "InputSystem.h"
#include "FontManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

#include "DebugTimer.h"



void Engine::Awake()
{
	// Win32 초기화
	ClientInitialize();

	// 엔진 초기화
	EngineInitialize();

	// 메인 루프 스레드
	UpdateMultiThread();
}

void Engine::ClientInitialize()
{
	WNDCLASSEXW wcex;
	{
		wcex.cbSize        = sizeof(WNDCLASSEX);
		wcex.style         = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc   = WndProc;
		wcex.cbClsExtra    = 0;
		wcex.cbWndExtra    = 0;
		wcex.hInstance     = Global::ClientOption.hInstance = GetModuleHandle(NULL);
		wcex.hIcon         = ::LoadIcon(NULL, IDI_WINLOGO);
		wcex.hCursor       = ::LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName  = NULL;
		wcex.lpszClassName = Global::ClientOption.appName.c_str();
		wcex.hIconSm       = wcex.hIcon;
	}
	RegisterClassExW(&wcex);

	RECT windowRect = { 0, 0, Global::ClientOption.width, Global::ClientOption.height };
	::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	Global::ClientOption.hWnd = CreateWindowW
	(
		Global::ClientOption.appName.c_str(),
		Global::ClientOption.appName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,
		nullptr,
		Global::ClientOption.hInstance,
		nullptr
	);

	if (!Global::ClientOption.hWnd)
	{
		return;
	}

	::ShowWindow(Global::ClientOption.hWnd, SW_SHOWNORMAL);
	::UpdateWindow(Global::ClientOption.hWnd);
}

void Engine::EngineInitialize()
{
	LOG     .Awake();
	TIMER   .Awake();
	INPUT   .Awake();
	DIRECTX .Awake();
	ASSET   .Awake();
	FONT	.Awake();
	RENDERER.Awake();
	SOUND   .Awake();
	SCENE   .Awake();
}

void Engine::UpdateMultiThread()
{
	// 업데이트, 렌더 스레드 실행
	renderThread = std::thread(&Engine::RenderThread, this);

	// FixedUpdate
	f64 acc = 0.f;
	f64 FIXED_DELTA = 1.f / 60.f;

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		//TimeMeasurement totalFrameTimer;


		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
		{
			aRunning = false;
			semBufferFreeSignal.release();
			semRenderReadySignal.release();
		}

		acc += TIMER.DeltaTime();

		while (acc >= FIXED_DELTA)
		{
			SCENE.FixedUpdate();
			COLLISION.FixedUpate();
			acc = 0.f;
		}

		TIMER.Update();
		INPUT.Update();
		SOUND.Update();

		SCENE.Update();
		SCENE.LateUpdate();

		semBufferFreeSignal.acquire();
		{
			RENDERER.CollectRenderData();
			std::lock_guard<std::mutex> lock(mtx);
			RENDERER.SwapTripleContext();
		}
		semRenderReadySignal.release();
	}

	SCENE.SaveScene();
	SOUND.Destroy();

	semBufferFreeSignal.release();
	semRenderReadySignal.release();

	renderThread.join();
}

void Engine::RenderThread()
{
	while (aRunning.load())
	{
		semRenderReadySignal.acquire();

		if (!aRunning.load()) break;

		DIRECTX.RenderBegin();
		RENDERER.RenderGameObject();
		DIRECTX.RenderEnd();

		semBufferFreeSignal.release();
	}
}

LRESULT CALLBACK Engine::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:

			DestroyWindow(handle);
			break;
		}
		break;

	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return ::DefWindowProc(handle, message, wParam, lParam);
}