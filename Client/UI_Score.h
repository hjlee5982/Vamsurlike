#pragma once

#include "Component.h"

class UIText;

class UI_Score : public Component
{
public:
	virtual void Awake() override;
public:
	bool Refresh(const struct RefreshUIEvent& e);
private:
	sptr<UIText> _scoreText;
	i32 _score = 0;
};

