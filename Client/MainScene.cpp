#include "pch.h"
#include "MainScene.h"
#include "GameObject.h"
#include "Camera.h"
#include "BackgroundController.h"
#include "PlayerController.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "ObjectGenerator.h"
#include "RenderManager.h"
#include "UIText.h"
#include "BoxCollider2D.h"
#include "InputSystem.h"
#include "Transform.h"
#include "UIBoundary.h"
#include "UI_Score.h"
#include "GameManager.h"
#include "UIImage.h"
#include "SoundManager.h"
#include "CircleCollider2D.h"

void MainScene::Initialize()
{
	// 리소스 로드
	LoadResources();

	//// 인풋 설정
	SetInputSystem();

	//// 오브젝트 배치
	AddGameObject();

	//// 엔진 설정
	EngineSetting();
}

void MainScene::LoadResources()
{
	// 배경화면
	{
		ASSET.LoadTexture(L"Texture_BackGround", L"../Assets/Image/BackGround.png");
	}
	// 플레이어
	{
		for (int i = 1; i <= 10; ++i)
		{
			ASSET.LoadTexture(L"Texture_Player_" + std::to_wstring(i), L"../Assets/Image/Player/Player_" + std::to_wstring(i) + L".png");
		}
	}
	// 장애물(구름)
	{
		ASSET.LoadTexture(L"Texture_Cloud", L"../Assets/Image/Cloud.png");
	}
	// 장애물(밧줄)
	{
		ASSET.LoadTexture(L"Texture_Rope", L"../Assets/Image/Rope.png");
	}
	// 사운드
	{
		SOUND.LoadSound("BGM.mp3");
		SOUND.LoadSound("Jump.mp3");
		SOUND.LoadSound("Effect.mp3");
		SOUND.LoadSound("Crash.mp3");
		SOUND.LoadSound("Open.mp3");

		SOUND.PlayBGM("BGM", 0.3f);
	}
}

void MainScene::SetInputSystem()
{
	InputMap map;
	{
		map.AddAction("Start", { 'R'});
		map.AddAction("Jump", { 'E', VK_SPACE});
	}
	INPUT.AddMap(map);
}

void MainScene::AddGameObject()
{
	// 카메라
	auto camera = Instantiate();
	{
		{
			camera->name = "MainCamera";
		}
		{
			auto tf = camera->AddComponent<Transform>();
			auto cm = camera->AddComponent<Camera>();
			{
				CameraDesc desc;
				{
					desc.Type      = ProjectionType::Orthogonal;
					desc.Near      = 0.3f;
					desc.Far       = 1000.f;
					desc.OrthoSize = 5.f;
				}
				cm->Initialize(desc);
			}
		}
	}
	// 배경화면 제어기
	auto bgCtrler = Instantiate();
	{
		bgCtrler->AddComponent<BackgroundController>();
	}
	
	// 바운더리(천장)
	auto topBoundary = Instantiate();
	{
		{
			topBoundary->name = "TopBoundary";
			topBoundary->tag  = "Boundary";
		}
		auto tf = topBoundary->AddComponent<Transform>();
		{
			tf->SetScale(Vector3(8.f, 0.01f, 0.f));
			tf->SetPosition(Vector3(0.f, 5.f, 0.f));
		}
		topBoundary->AddComponent<BoxCollider2D>();
	}
	// 바운더리(바닥)
	auto btmBoundary = Instantiate();
	{
		{
			btmBoundary->name = "BtmBoundary";
			btmBoundary->tag  = "Boundary";
		}
		auto tf = btmBoundary->AddComponent<Transform>();
		{
			tf->SetScale(Vector3(8.f, 0.01f, 0.f));
			tf->SetPosition(Vector3(0.f, -5.f, 0.f));
		}
		btmBoundary->AddComponent<BoxCollider2D>();
	}
	// 장애물 생성기
	auto oj = Instantiate();
	{
		oj->name = "ObstacleGenerator";
		oj->AddComponent<ObjectGenerator>();
		oj->SetActive(false);
	}
	// 플레이어
	auto player = Instantiate();
	{
		{
			player->name = "Player";
			player->tag  = "Player";
		}
		auto tf = player->AddComponent<Transform>();
		{
			tf->SetScale(Vector3(2.f, 2.f, 1.f));
			tf->SetPosition(Vector3(-1.5f, 1.f, 0.f));
		}
		auto sr = player->AddComponent<SpriteRenderer>();
		{
			sr->SetTexture(L"Texture_Player_1");
			sr->OrderInLayer = 30;
		}
		auto bc = player->AddComponent<BoxCollider2D>();
		{
			bc->Size(Vector3(0.25f, 0.25f, 0.25f));
			bc->Offset(Vector3(0.02f, 0.f, 0.f));
		}
		player->AddComponent<PlayerController>();
	}
	// 스코어 UI
	auto scoreUI = Instantiate();
	{
		{
			scoreUI->name = "ScoreUI";
		}
		auto tr = scoreUI->AddComponent<Transform>();
		{
			tr->SetPosition(Vector3(-260.f, 440.f, 0.f));
			tr->SetScale(Vector3(120.f, 80.f, 0.f));
		}
		auto ut = scoreUI->AddComponent<UIText>();
		{
			ut->Text(L"000");
			ut->Alignment(EHorizontalAlignment::Center, EVerticalAlignment::Top);
			ut->Scale(60);
			ut->Space(4);
		}
		scoreUI->AddComponent<UI_Score>();
		scoreUI->SetActive(false);
	}
	// 타이틀 UI
	auto titleUI = Instantiate();
	{
		{
			titleUI->name = "TitleUI";
		}
		auto tr = titleUI->AddComponent<Transform>();
		{
			tr->SetScale(Vector3(Global::ClientOption.width , Global::ClientOption.height, 1.f));
		}
		auto im = titleUI->AddComponent<UIImage>();
		{
			im->color = Vector4(0.f, 0.f, 0.f, 0.5f);
		}

		auto desc_1 = Instantiate();
		{
			auto descTr = desc_1->AddComponent<Transform>();
			{
				descTr->SetParent(tr);
				descTr->SetScale(Vector3(200.f, 50.f, 1.f));
				descTr->SetPosition(Vector3(0.f, -150.f, 0.f));
			}
			auto descText = desc_1->AddComponent<UIText>();
			{
				descText->Text(L"조작 : SPACE");
				descText->Alignment(EHorizontalAlignment::Center);
				descText->Scale(48);
			}
		}
		auto desc_2 = Instantiate();
		{
			auto descTr = desc_2->AddComponent<Transform>();
			{
				descTr->SetParent(tr);
				descTr->SetScale(Vector3(200.f, 50.f, 1.f));
				descTr->SetPosition(Vector3(0.f, -250.f, 0.f));
			}
			auto descText = desc_2->AddComponent<UIText>();
			{
				descText->Text(L"종료 : ESC");
				descText->Alignment(EHorizontalAlignment::Center);
				descText->Scale(48);
			}
		}
		auto desc_3 = Instantiate();
		{
			auto descTr = desc_3->AddComponent<Transform>();
			{
				descTr->SetParent(tr);
				descTr->SetScale(Vector3(200.f, 50.f, 1.f));
				descTr->SetPosition(Vector3(0.f, -350.f, 0.f));
			}
			auto descText = desc_3->AddComponent<UIText>();
			{
				descText->Text(L"- R 키를 눌러 시작 -");
				descText->Alignment(EHorizontalAlignment::Center);
				descText->Scale(32);
			}
		}
	}
	// 게임오버 UI
	auto gameOverUI = Instantiate();
	{
		// 부모 컴포넌트
		auto tr = gameOverUI->AddComponent<Transform>();
		{
			tr->SetScale(Vector3(Global::ClientOption.width, Global::ClientOption.height, 1.f));
		}
		auto im = gameOverUI->AddComponent<UIImage>();
		{
			im->color = Vector4(0.f, 0.f, 0.f, 0.5f);
		}

		// 자식 1
		auto desc_1 = Instantiate();
		{
			auto descTr = desc_1->AddComponent<Transform>();
			{
				descTr->SetParent(tr);
				descTr->SetScale(Vector3(200.f, 50.f, 1.f));
				descTr->SetPosition(Vector3(0.f, -150.f, 0.f));
			}
			auto descText = desc_1->AddComponent<UIText>();
			{
				descText->Text(L"다시 시작 : R");
				descText->Alignment(EHorizontalAlignment::Center);
				descText->Scale(48);
			}
		}
		// 자식 2
		auto desc_2 = Instantiate();
		{
			auto descTr = desc_2->AddComponent<Transform>();
			{
				descTr->SetParent(tr);
				descTr->SetScale(Vector3(200.f, 50.f, 1.f));
				descTr->SetPosition(Vector3(0.f, -250.f, 0.f));
			}
			auto descText = desc_2->AddComponent<UIText>();
			{
				descText->Text(L"종료 : ESC");
				descText->Alignment(EHorizontalAlignment::Center);
				descText->Scale(48);
			}
		}
		// 자식 3
		auto result = Instantiate();
		{
			auto resultTr = result->AddComponent<Transform>();
			{
				resultTr->SetParent(tr);
				resultTr->SetScale(Vector3(200.f, 100.f, 1.f));
				resultTr->SetPosition(Vector3(0.f, 150.f, 0.f));
			}
			auto resultText = result->AddComponent<UIText>();
			{
				resultText->Text(L"점수 :");
				resultText->Alignment(EHorizontalAlignment::Center);
				resultText->Scale(48);
			}
		}
		gameOverUI->SetActive(false);
	}
	
	// 게임 매니저
	auto manager = Instantiate();
	{
		{
			manager->name = "GameManager";
		}
		auto mgr = manager->AddComponent<GameManager>();
		{
			mgr->_player       = player;
			mgr->_objGenerator = oj;
			mgr->_scoreUI      = scoreUI;
			mgr->_titleUI      = titleUI;
			mgr->_gameOverUI   = gameOverUI;
		}
	}
}


void MainScene::EngineSetting()
{
	RENDERER.colliderRendering = false;
	RENDERER.debugUIRendering  = false;
}
