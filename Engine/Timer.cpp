#include "pch.h"
#include "Timer.h"

void Timer::Awake()
{
	_timePoint = std::chrono::steady_clock::now();
}

void Timer::Update()
{
    auto now = std::chrono::steady_clock::now();

    std::chrono::duration<f64> sec = now - _timePoint;

    _realDeltaTime = sec.count();

    _deltaTime = _realDeltaTime * _timeScale;

    _timePoint = now;
}