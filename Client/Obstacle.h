#pragma once

#include "Component.h"

class Obstacle : public Component
{
public:
	virtual void Awake() override;
	virtual void Update() override;
public:
	bool GameOver(const struct GameOverEvent& e);
public:
	void SetGenerator(sptr<class ObjectGenerator> generator)
	{
		_generator = generator;
	}
private:
	f32 _speed = 3.f;
private:
	wptr<class ObjectGenerator> _generator;
public:
	bool _isColliding = false;
};

