#include "pch.h"
#include "PlayerController.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "Texture.h"
#include <variant>
#include "InputSystem.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoxCollider2D.h"
#include "Event.h"
#include "EventManager.h"
#include "Obstacle.h"
#include "Checker.h"
#include "Event.h"
#include "EventManager.h"
#include "SoundManager.h"

void PlayerController::Start()
{
	_sr = GetComponent<SpriteRenderer>();

	EVENT::Subscribe<GameStartEvent>(&PlayerController::GameStart, this);
	EVENT::Subscribe<GameOverEvent>(&PlayerController::GameOver, this);

	//INPUT.FindAction("Jump")->performed = [this]() { Jump(); };
	INPUT.FindAction("Jump")->started = std::bind(&PlayerController::Jump, this);
}

void PlayerController::Update()
{
	TempAnimation();

	if (_trigger == true)
	{
		Vector3	pos = Owner()->transform->GetPosition();
		Vector3 up = Owner()->transform->GetUp();

		up.Normalize();

		f32 gravity = -9.81f * 4.f;

		_velocity += gravity * TIMER.DeltaTime();

		pos += up * _velocity * TIMER.DeltaTime();

		Owner()->transform->SetPosition(pos);
	}
}

void PlayerController::Reset()
{
	_trigger = false;
	Owner()->transform->SetPosition(Vector3(-1.5f, 1.f, 0.f));
}

void PlayerController::OnCollisionEnter2D(sptr<Collider> collider)
{
	if (collider->Owner()->tag == "Obstacle")
	{
		SOUND.PlaySFX("Crash", 0.2f);
		EVENT::SendEvent(GameOverEvent{});
	}
	else if (collider->Owner()->tag == "Boundary")
	{
		SOUND.PlaySFX("Crash", 0.2f);
		EVENT::SendEvent(GameOverEvent{});
	}
	else if (collider->Owner()->tag == "Checker")
	{
		auto checker = collider->Owner()->GetComponent<Checker>();

		if (checker != nullptr && checker->_isColliding == false)
		{
			SOUND.PlaySFX("Effect", 0.2f);

			EVENT::SendEvent(AddScoreEvent{});

			checker->_isColliding = true;
		}
	}
}

void PlayerController::Jump()
{
	if (_isStart == false)
	{
		return;
	}
	else
	{
		SOUND.PlaySFX("Jump", 0.2f);

		if (_trigger == false)
		{
			_trigger = true;
		}

		_velocity = 8.f;
		_index = 5;
	}
}

bool PlayerController::GameStart(const GameStartEvent& e)
{
	_isStart = true;

	return false;
}

bool PlayerController::GameOver(const GameOverEvent& e)
{
	_isStart = false;

	return false;
}

void PlayerController::TempAnimation()
{
	_elapsed += TIMER.DeltaTime();

	if (_elapsed >= 0.05f)
	{
		_sr->SetTexture(L"Texture_Player_" + std::to_wstring(_index));

		_elapsed = 0.f;

		++_index;

		if (_index > 10)
		{
			_index = 1;
		}
	}
}
