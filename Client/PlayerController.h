#pragma once

#include "Component.h"

class PlayerController : public Component
{
public:
	virtual void Start()       override;
	virtual void Update()      override;
public:
	void Reset();
public:
	virtual void OnCollisionEnter2D(sptr<Collider> collider) override;
private:
	void Jump();
	bool GameStart(const struct GameStartEvent& e);
	bool GameOver(const struct GameOverEvent& e);
private:
	void TempAnimation();
private:
	bool _isStart = false;
	bool _trigger = false;
	f32 _velocity = 5.f;
	f32 _elapsed = 0.f;
	i32 _index = 1;
	sptr<class SpriteRenderer> _sr;
};

