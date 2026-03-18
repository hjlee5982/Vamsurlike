#pragma once

struct ClientOption
{
	HWND      hWnd;

	HINSTANCE hInstance;
	bool      vsync;
	Color     clearColor;

	wstring   appName;
	f32       width;
	f32       height;
	bool      windowed;
};

class Engine : public Singleton<Engine>
{
public:
	virtual void Awake() override;
private:
	void ClientInitialize();
	void EngineInitialize();
private:
	void UpdateSingleThread();
	void UpdateMultiThread();
public:
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);


	// 멀티스레딩
private:
	std::mutex mtx;
	std::atomic<bool> aRunning = true;
private:
	std::thread renderThread;
private:
	void RenderThread();
private:
	std::binary_semaphore semRenderReadySignal{ 0 };
	std::binary_semaphore semBufferFreeSignal{ 1 };

private:
	i32 ThreadIdx = 1;

	// 성능 디버깅
private:
	i32 frameCount = 0;
	f64 cumulativeCpuWaitTime = 0.0;
	f64 cumulativeTotalFrameTime = 0.0;

	std::chrono::high_resolution_clock::time_point lastLogTime =
		std::chrono::high_resolution_clock::now();

	const f64 LOG_INTERVAL_SEC = 1.0f;

private:
	i32 stFrameCount = 0;
	f64 stCumulativeTotalFrameTime = 0.0;
	f64 stCumulativeCpuWorkTime = 0.0;

	std::mutex g_log_mutex;



private:
	void UHT();
};

