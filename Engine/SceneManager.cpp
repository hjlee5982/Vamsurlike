#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"

namespace fs = std::filesystem;

void SceneManager::Awake()
{
	auto scene = _currentScene.lock();

	if (scene)
	{
		_currentScene.lock()->Initialize();
		_currentScene.lock()->Awake();
	}
}

void SceneManager::LoadScene()
{
}

void SceneManager::SaveScene()
{
	for (auto& [name, scene] : _scenes)
	{
		scene->Save(name + ".json");
	}
}

void SceneManager::AddScene(const string& name, sptr<class Scene> scene)
{
	_scenes[name] = scene;

	_currentScene = scene;
}

void SceneManager::AddGameObject(sptr<class GameObject> go)
{
	auto scene = _currentScene.lock();

	if (scene)
	{
		scene->AddGameObject(go);
	}
}

void SceneManager::Start()
{
	auto scene = _currentScene.lock();

	if (scene)
	{
		scene->Start();
	}
}

void SceneManager::Update()
{
	auto scene = _currentScene.lock();

	if (scene)
	{
		scene->Update();
	}
}

void SceneManager::LateUpdate()
{
	auto scene = _currentScene.lock();

	if (scene)
	{
		scene->LateUpdate();
	}
}

void SceneManager::FixedUpdate()
{
	auto scene = _currentScene.lock();

	if (scene)
	{
		scene->FixedUpdate();
	}
}

void SceneManager::Destroy(sptr<GameObject> go)
{
	auto scene = _currentScene.lock();

	if (scene)
	{
		scene->Destroy(go);
	}
}

