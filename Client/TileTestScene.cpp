#include "pch.h"
#include "TileTestScene.h"

#include "AssetManager.h"
#include "RenderManager.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider2D.h"
#include "Tilemap.h"
#include "TilemapRenderer.h"

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
			{
				tileMap->SetTile(0, 0, 1, 1);
				tileMap->SetTile(0, 0, 0, 0);
			}
		}
		auto tilemapRenderer = tile->AddComponent<TilemapRenderer>();
		{
			tilemapRenderer->SetTilemap(tileMap);
		}
	}
}

void TileTestScene::EngineSetting()
{
	RENDERER.colliderRendering = true;
}
