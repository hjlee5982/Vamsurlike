#include "pch.h"
#include "BackgroundController.h"
#include "Texture.h"
#include "AssetManager.h"
#include "BoxCollider2D.h"
#include "SpriteRenderer.h"
#include "Transform.h"

void BackgroundController::Start()
{
	_bg1 = Instantiate();
	{
		auto tf = _bg1->AddComponent<Transform>();
		{
			tf->SetScale(Vector3(20.f, 10.f, 1.f));
		}
		auto sr = _bg1->AddComponent<SpriteRenderer>();
		{
			sr->SetTexture(L"Texture_BackGround");
		}
	}
	_bg2 = Instantiate();
	{
		auto tf = _bg2->AddComponent<Transform>();
		{
			tf->SetScale(Vector3(20.f, 10.f, 1.f));

			auto position = _bg2->transform->GetPosition();
			auto scale = _bg2->transform->GetScale();

			f32 delta = position.x + scale.x;

			tf->SetPosition(Vector3(delta, 0.f, 0.f));
		}
		auto sr = _bg2->AddComponent<SpriteRenderer>();
		{
			sr->SetTexture(L"Texture_BackGround");
		}
	}

	_scale = _bg1->transform->GetScale().x;
}

void BackgroundController::Update()
{

	auto bg1Pos = _bg1->transform->GetPosition();
	auto bg2Pos = _bg2->transform->GetPosition();

	bg1Pos.x -= _bgSpeed * TIMER.DeltaTime();
	bg2Pos.x -= _bgSpeed * TIMER.DeltaTime();

	if (bg1Pos.x <= -_scale)
	{
		bg1Pos.x = bg2Pos.x + _bg1->transform->GetScale().x;
	}
	if (bg2Pos.x <= -_scale)
	{
		bg2Pos.x = bg1Pos.x + _bg2->transform->GetScale().x;
	}

	_bg1->transform->SetPosition(bg1Pos);
	_bg2->transform->SetPosition(bg2Pos);

}

void BackgroundController::FixedUpdate()
{
	
}
