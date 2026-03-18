#include "pch.h"
#include "GameManager.h"
#include "Event.h"
#include "EventManager.h"
#include "Timer.h"
#include "InputSystem.h"
#include "ObjectGenerator.h"
#include "PlayerController.h"
#include "Transform.h"
#include "UIText.h"
#include "SoundManager.h"

void GameManager::Awake()
{
	EVENT::Subscribe<GameOverEvent>(&GameManager::GameOver, this);
	EVENT::Subscribe<AddScoreEvent>(&GameManager::AddScore, this);

	INPUT.FindAction("Start")->started = std::bind(&GameManager::GameStart, this);
}

void GameManager::GameStart()
{
	if (_isStart == false)
	{
		SOUND.PlaySFX("Open", 0.3f);

		_isStart = true;

		TIMER.TimeScale(1.f);

		EVENT::SendEvent(GameStartEvent{});
		EVENT::SendEvent(RefreshUIEvent{ _score });

		_scoreUI->SetActive(true);

		_objGenerator->SetActive(true);
		_objGenerator->GetComponent<ObjectGenerator>()->Reset();

		_player->SetActive(true);
		_player->GetComponent<PlayerController>()->Reset();

		_titleUI->SetActive(false);
		_gameOverUI->SetActive(false);
	}
}

bool GameManager::GameOver(const GameOverEvent& e)
{
	if (_isStart == true)
	{
		_gameOverUI->transform->GetChild(2)->GetComponent<UIText>()->Text(L"Á¡¼ö  :  " + std::to_wstring(_score));

		_score = 0;

		_isStart = false;

		TIMER.TimeScale(0.f);

		_player->SetActive(false);
		_scoreUI->SetActive(false);
		_objGenerator->SetActive(false);

		_gameOverUI->SetActive(true);
	}

	return false;
}

bool GameManager::AddScore(const AddScoreEvent& e)
{
	++_score;

	EVENT::SendEvent(RefreshUIEvent{ _score });

	return false;
}