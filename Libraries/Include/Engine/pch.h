#pragma once

#define _CRT_SECURE_NO_WARNINGS
/* C++ 헤더 */
#include <Windows.h>
#include <assert.h>
#include <optional>
#include <comdef.h>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <typeinfo>
#include <typeindex>
#include <array>
#include <chrono>
#include <fstream>
#include <variant>
#include <iostream>
#include <thread>
#include <coroutine>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <semaphore>

/* DirectX11 헤더 */
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>
#include <DirectXColors.h>
using namespace DirectX;
using namespace Microsoft::WRL;


/* DirectX11 라이브러리 */
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/DirectXTex_debug.lib")
#pragma comment(lib, "FX11/Effects11d.lib")
#pragma comment(lib, "FMOD/fmodL_vc.lib")
#else
#pragma comment(lib, "DirectXTex/DirectXTex.lib")
#pragma comment(lib, "FX11/Effects11.lib")
#pragma comment(lib, "FMOD/fmod_vc.lib")
#endif

/* 외부 라이브러리 */
#include "json.hpp"

/* Define */
#include "Define.h"
#include "Using.h"
#include "Singleton.h"

/* 사용자 */
#include "Log.h"
#include "Random.h"
#include "Engine.h"
#include "Device.h"
#include "Exception.h"
#include "Global.h"
#include "Timer.h"
#include "Instantiate.h"