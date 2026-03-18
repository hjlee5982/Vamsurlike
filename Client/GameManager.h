#pragma once

#include "Component.h"

class GameManager : public Component
{
public:
	virtual void Awake() override;
private:
	void GameStart();
	bool GameOver(const struct GameOverEvent& e);
	bool AddScore(const struct AddScoreEvent& e);
public:
	sptr<class GameObject> _player;
	sptr<class GameObject> _objGenerator;
	sptr<class GameObject> _scoreUI;
	sptr<class GameObject> _titleUI;
	sptr<class GameObject> _gameOverUI;
private:
	bool _isStart = false;
private:
	i32 _score = 0;
};

