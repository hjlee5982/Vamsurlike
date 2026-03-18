#include "pch.h"
#include "Scene.h"
#include "Transform.h"
#include "Camera.h"

void Scene::Save(const string& path)
{
	nlohmann::json json;
	json["gameObjects"] = nlohmann::json::array();

	for (const auto& obj : _gameObjects)
	{
		json["gameObjects"].push_back(obj->MakeJson());
	}
	for (const auto& obj : _uiObjects)
	{
		json["gameObjects"].push_back(obj->MakeJson());
	}

	std::ofstream file(path);
	file << json.dump(4);
}

void Scene::AddGameObject(sptr<class GameObject> go)
{
	_newObjects.push_back(go);
}

void Scene::Awake()
{
	// 기본 카메라
	auto mainCam = Instantiate();
	{
		{
			mainCam->name = "MainCamera";
		}
		{
			auto tf = mainCam->AddComponent<Transform>();
			auto cm = mainCam->AddComponent<Camera>();
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

	// 기본 UI 카메라
	auto uiCam = Instantiate();
	{
		{
			uiCam->name = "UICamera";
		}
		auto tf = uiCam->AddComponent<Transform>();
		auto cm = uiCam->AddComponent<Camera>();
		{
			CameraDesc desc;
			{
				desc.Type = ProjectionType::OrthoUI;
			}
			cm->Initialize(desc);
		}
	}
}

void Scene::Start()
{
}

void Scene::Update()
{
	for (auto& go : _newObjects)
	{
		_pendingAwake.push_back(go);
	}
	_newObjects.clear();


	for (auto& go : _pendingAwake)
	{
		go->Awake();
	}
	_pendingStart.insert(_pendingStart.end(), _pendingAwake.begin(), _pendingAwake.end());
	_pendingAwake.clear();


	for (auto& go : _pendingStart)
	{
		_gameObjects.push_back(go);
	}
	for (auto& go : _pendingStart)
	{
		go->Start();
	}
	_pendingStart.clear();


	for (auto& go : _gameObjects)
	{
		if (go->isActive == true)
		{
			go->Update();
		}
	}

	for (auto& go : _destroyObjects)
	{
		_gameObjects.erase(remove(_gameObjects.begin(), _gameObjects.end(), go), _gameObjects.end());
	}
	_destroyObjects.clear();
}

void Scene::LateUpdate()
{
	for (auto& go : _gameObjects)
	{
		if (go->isActive == true)
		{
			go->LateUpdate();
		}
	}
}

void Scene::FixedUpdate()
{
	for (auto& go : _gameObjects)
	{
		if (go->isActive == true)
		{
			go->FixedUpdate();
		}
	}
}

void Scene::Destroy(sptr<class GameObject> go)
{
	_destroyObjects.push_back(go);
}
