#pragma once

class TimeMeasurement
{
public:
	// 시작 시간 기록
	TimeMeasurement()
		: start_time_(std::chrono::high_resolution_clock::now()) {}

	// 경과 시간(마이크로초)을 반환
	f64 GetDurationUs() const
	{
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time_);
		return (f64)duration.count();
	}
private:
	std::chrono::high_resolution_clock::time_point start_time_;
};