#pragma once

#include "SceneManager.h"
#include "GameObject.h"
#include "Transform.h"

static uint64_t nextID = 1;

template<typename... Args>
static sptr<GameObject> Instantiate(Args&&... args)
{
	sptr<GameObject> go = makeSptr<GameObject>();

	go->id = nextID++;

	go->transform = go->AddComponent<Transform>(std::forward<Args>(args)...);

	SCENE.AddGameObject(go);

	return go;
}

static void Destroy(sptr<GameObject> go)
{
	SCENE.Destroy(go);
}