#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"

nlohmann::json GameObject::MakeJson()
{
	nlohmann::json json;

	json["name"] = name;
	json["id"] = id;
	json["components"] = nlohmann::json::array();

	/*for (const auto& com : _components)
	{
		nlohmann::json comJson;
	}*/

	return json;
}

void GameObject::LoadJson(const nlohmann::json& json)
{

}

void GameObject::Awake()
{
	for (auto& com : _components)
	{
		com.second->Awake();
	}
}

void GameObject::Start()
{
	for (auto& com : _components)
	{
		com.second->Start();
	}
}

void GameObject::Update()
{
	for (auto& com : _components)
	{
		com.second->Update();
	}
}

void GameObject::LateUpdate()
{
	for (auto& com : _components)
	{
		com.second->LateUpdate();
	}
}

void GameObject::FixedUpdate()
{
	for (auto& com : _components)
	{
		com.second->FixedUpdate();
	}
}

void GameObject::SetActive(bool active)
{
	isActive = active;

	transform->SetActive(active);
}

void GameObject::OnCollisionEnter2D(sptr<Collider> collider)
{
	for (auto& com : _components)
	{
		com.second->OnCollisionEnter2D(collider);
	}
}