#pragma once

#include <random>

class Random : public Singleton<Random>
{
public:
	int Range(int min, int max)
	{
		std::mt19937 rng(std::random_device{}());

		std::uniform_int_distribution<int> dist(min, max - 1);

		return dist(rng);
	}
	float Range(float min, float max)
	{
		std::mt19937 rng(std::random_device{}());

		std::uniform_real_distribution<float> dist(min, max);

		return dist(rng);
	}
};

