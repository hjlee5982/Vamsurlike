#include "pch.h"
#include "TileTestScene.h"

#include "AssetManager.h"
#include "RenderManager.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider2D.h"
#include "Tilemap.h"
#include "TilemapRenderer.h"
#include "InputSystem.h"

#include "TestController.h"


void TileTestScene::Initialize()
{
	LoadResources();

	SetInputSystem();

	AddGameObject();

	EngineSetting();
}

void TileTestScene::LoadResources()
{
	// 타일 스프라이트
	{
		ASSET.LoadTexture(L"Texture_Tile", L"../Assets/Image/Tile.png");
	}
}

void TileTestScene::SetInputSystem()
{
}

void TileTestScene::AddGameObject()
{
	auto tile = Instantiate();
	{
		auto transform = tile->AddComponent<Transform>();
		{
			transform->SetScale(Vector3(0.5f, 0.5f, 0.5f));
		}
		auto tileMap = tile->AddComponent<Tilemap>();
		{
			tileMap->SetTileSprite(L"Texture_Tile", 16);

			i32 width  = 32;
			i32 height = 18;

			i32 left  = (width * -1) / 2;
			i32 right = (left * -1) - 1;
			i32 top   = (height / 2) - 1;
			i32 btm   = (top * -1) -1;

			// 모퉁이
			{
				tileMap->SetTile(0, 6, left, top);
				tileMap->SetTile(2, 6, right, top);
				tileMap->SetTile(0, 4, left, btm);
				tileMap->SetTile(2, 4, right, btm);
			}
			// 상하
			{
				for (i32 i = left + 1; i < right; ++i)
				{
					tileMap->SetTile(1, 6, i, top);
					tileMap->SetTile(1, 4, i, btm);
				}
			}
			// 좌우
			{
				for (i32 i = btm + 1; i < top; ++i)
				{
					tileMap->SetTile(0, 5, left, i);
					tileMap->SetTile(2, 5, right, i);
				}
			}
			// 내부
			{
				for (i32 i = left + 1; i < right; ++i)
				{
					for (i32 j = btm + 1; j < top; ++j)
					{
						if (RANDOM.Range(1, 10) >= 9)
						{
							tileMap->SetTile(RANDOM.Range(0, 5), RANDOM.Range(0, 1), i, j);
						}
						else
						{
							tileMap->SetTile(1, 5, i, j);
						}
					}
				}
			}
		}
		auto tilemapRenderer = tile->AddComponent<TilemapRenderer>();
		{
			tilemapRenderer->Grid = false;
			tilemapRenderer->SetTilemap(tileMap);
		}
	}

	auto player = Instantiate();
	{
		auto t = player->AddComponent<Transform>();
		{
			t->SetScale(Vector3(2.f, 2.f, 2.f));
			t->SetPosition(Vector3(0.f, 0.f, 0.f));
		}
		player->AddComponent<SpriteRenderer>();
		{

		}
		player->AddComponent<TestController>();
		{

		}
	}
}

void TileTestScene::EngineSetting()
{
	RENDERER.colliderRendering = true;
	RENDERER.pointSampling     = true;
}
