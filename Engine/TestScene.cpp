#include "pch.h"
#include "TestScene.h"
#include<fstream>

#include "TestGameObject.h"

TestGameObject* TestScene::CreateObject()
{
    auto obj = new TestGameObject();

    _objects.push_back(obj);

    _objectMap[obj->id] = obj;

    return obj;
}

void TestScene::Save(const string& path)
{
    nlohmann::json json;
    json["gameObjects"] = nlohmann::json::array();

    for (const auto& obj : _objects)
    {
        json["gameObjects"].push_back(obj->MakeJson());
    }

    std::ofstream file(path);
    file << json.dump(4);
}

void TestScene::Load(const string& path)
{
    std::ifstream file(path);

    nlohmann::json json;
    file >> json;

    uint64_t maxID = 0;

    TypeRegistry::resolver = [this](uint64_t id)
        {
            return FindObject(id);
        };
    TypeRegistry::componentResolver = [this](uint64_t id)
        {
            return FindComponent(id);
        };

    for (const auto& objJson : json["gameObjects"])
    {
        auto obj = new TestGameObject();

        obj->id = objJson["id"];
        _objectMap[obj->id] = obj;

        if (obj->id >= maxID)
        {
            maxID = obj->id;
        }

        _objects.push_back(obj);
    }

    for (i32 i = 0; i < _objects.size(); ++i)
    {
        _objects[i]->LoadJson(json["gameObjects"][i]);
    }
}

TestGameObject* TestScene::FindObject(uint64_t id)
{
    auto it = _objectMap.find(id);

    if (it != _objectMap.end())
    {
        return it->second;
    }

    return nullptr;
}

TestComponent* TestScene::FindComponent(uint64_t id)
{
    auto it = _componentMap.find(id);

    if (it != _componentMap.end())
    {
        return it->second;
    }

    return nullptr;
}
