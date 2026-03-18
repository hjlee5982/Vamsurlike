#pragma once

#include "Component.h"

class ObjectGenerator : public Component, public std::enable_shared_from_this<ObjectGenerator>
{
public:
	virtual void Start() override;
	virtual void Update() override;
public:
	void ReturnPool(sptr<class GameObject> obj, int idx);
	void Reset();
private:
	void Generate();
private:
	void ObstaclePooling();
	void CheckerPooling();
private:
	std::queue<sptr<class GameObject>> _obstacles;
	std::queue<sptr<class GameObject>> _checkers;
private:
	f32 _elapsed   = 0.f;
	f32 _frequency = 2.f;
	i32 _poolSize  = 4;
};

