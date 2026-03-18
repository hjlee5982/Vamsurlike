#pragma once

class Timer : public Singleton<Timer>
{
public:
	virtual void Awake() override;
public:
	void Update();
public:
	void TimeScale(f32 timeScale)
	{
		_timeScale = timeScale;
	}
public:
	const f32 DeltaTime()
	{
		return _deltaTime;
	}
	const f32 FixedDeltaTime()
	{
		return _fixedDeltaTime;
	}
	const f32 FPS()
	{
		return _FPS;
	}
private:
	std::chrono::steady_clock::time_point _timePoint;
public:
	f32 _timeScale = 1.f;
private:
	f64 _deltaTime     = 0.0f;
	f64 _realDeltaTime = 0.0f;
private:
	f64 _totalTime = 0.0f;
	f64 _fixedDeltaTime = 1.f / 60.f;
	f64 _elapsed   = 0.0f;
private:
	u32 _FPS        = 0;
	u32 _frameCount = 0;

};


