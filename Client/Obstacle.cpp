#include "pch.h"
#include "Obstacle.h"
#include "ObjectGenerator.h"
#include "GameObject.h"
#include "Transform.h"
#include "EventManager.h"
#include "Event.h"

void Obstacle::Awake()
{
	EVENT::Subscribe<GameOverEvent>(&Obstacle::GameOver, this);
}

void Obstacle::Update()
{
	Owner()->transform->Translation(-Vector3::Right, _speed *TIMER.DeltaTime());

	auto position = Owner()->transform->GetPosition();

	if (position.x <= -4.f)
	{
		_isColliding = false;
		_generator.lock()->ReturnPool(Owner(), 0);
	}
}

bool Obstacle::GameOver(const GameOverEvent& e)
{
	_isColliding = false;

	_generator.lock()->ReturnPool(Owner(), 0);

	return false;
}
