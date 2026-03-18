#include "pch.h"
#include "UI_Score.h"
#include "InputSystem.h"
#include "UIText.h"
#include <format>
#include "Event.h"
#include "EventManager.h"

void UI_Score::Awake()
{
	_scoreText = Owner()->GetComponent<UIText>();

	EVENT::Subscribe<RefreshUIEvent>(&UI_Score::Refresh, this);
}

bool UI_Score::Refresh(const RefreshUIEvent& e)
{
	wstring wstr = std::format(L"{:03}", e.score);
	
	_scoreText->Text(wstr);

	return true;
}