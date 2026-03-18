#pragma once

#include "TestComponent.h"

static uint64_t nextIDtest = 1;

class TestGameObject
{
public:
	TestGameObject()
	{
		id = nextIDtest++;
	}
public:
	nlohmann::json MakeJson() const;
	void LoadJson(const nlohmann::json& json);
public:
	TestComponent* AddComponent(const string& typeName);
	TestComponent* AddComponent1(const string& typeName);
private:
	List<uptr<TestComponent>> _components;
public:
	string name;
public:
	class TestTransform* _transform;
public:
	uint64_t id;
};

