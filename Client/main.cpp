#include "pch.h"
#include "SceneManager.h"

#include "MainScene.h"
#include "TileTestScene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	AllocConsole();

	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	freopen_s(&fp, "CONIN$", "r", stdin);

	ClientOption option;
	{
		option.hInstance  = hInstance;
		option.vsync      = false;
		option.clearColor = Color(Colors::Blue);

		option.appName  = L"Vamsurlike";
		option.width    = 1920;
		option.height   = 1090;
		option.windowed = false;
	}
	Global::ClientOption = option;

	//sptr<MainScene> scene = makeSptr<MainScene>();
	auto scene = makeSptr<TileTestScene>();

	SCENE.AddScene("TileTestScene", scene);
	ENGINE.Awake();

	FreeConsole();

	return 0;
}