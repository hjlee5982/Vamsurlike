#pragma once

class TestScene
{
public:
	class TestGameObject* CreateObject();
public:
	void Save(const string& path);
	void Load(const string& path);
public:
	List<class TestGameObject*> _objects;
public:
	Dictionary<uint64_t, class TestGameObject*> _objectMap;
	Dictionary<uint64_t, class TestComponent*> _componentMap;
public:
	class TestGameObject* FindObject(uint64_t id);
	class TestComponent* FindComponent(uint64_t id);
};

