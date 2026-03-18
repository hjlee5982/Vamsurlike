#include "pch.h"
#include "TypeRegister.h"
#include "Component.h"

void TypeRegister::Register(const string& name, CreateComponentFunc func)
{
    GetCreator()[name] = func;
}

uptr<Component> TypeRegister::CreateComponent(const string& name)
{
    auto& typeData = GetTypeData();

    auto it = typeData.find(name);

    if (it == typeData.end())
    {
        return nullptr;
    }

    return it->second.creator();
}

TypeInfo* TypeRegister::RegisterType(const string& name, std::function<uptr<Component>()> creator, const string& parentName)
{
    auto& typeData = GetTypeData();

    TypeData data;
    {
        data.creator = creator;
        data.typeInfo = makeUptr<TypeInfo>();
        {
            data.typeInfo->typeName = name;
            data.typeInfo->parentName = parentName;
        }
    }
    typeData[name] = std::move(data);

    return typeData[name].typeInfo.get();
}

TypeInfo* TypeRegister::GetTypeInfo(const string& name)
{
    auto& typeData = GetTypeData();

    auto it = typeData.find(name);

    if (it == typeData.end())
    {
        return nullptr;
    }

    return it->second.typeInfo.get();
}

Dictionary<string, TypeRegister::CreateComponentFunc>& TypeRegister::GetCreator()
{
    static Dictionary<string, TypeRegister::CreateComponentFunc> creator;

    return creator;
}

Dictionary<string, TypeData>& TypeRegister::GetTypeData()
{
    static Dictionary<string, TypeData> typeData;

    return typeData;
}

void TypeRegister::SerializeType(void* obj, TypeInfo* type, nlohmann::json& json)
{
    if (type->parent != nullptr)
    {
        SerializeType(obj, type->parent, json);
    }

    for (auto& field : type->fields)
    {
        field->serialize(obj, json);
    }
}

void TypeRegister::DeserializeType(void* obj, TypeInfo* type, const nlohmann::json& json)
{
    if (type->parent != nullptr)
    {
        DeserializeType(obj, type->parent, json);
    }

    for (auto& field : type->fields)
    {
        field->deserialize(obj, json);
    }
}

void TypeRegister::ResolveParents()
{
    auto& typeData = GetTypeData();

    for (auto& [name, data] : typeData)
    {
        auto& type = data.typeInfo;

        if (type->parentName.empty())
        {
            continue;
        }

        auto it = typeData.find(type->parentName);

        if (it != typeData.end())
        {
            type->parent = it->second.typeInfo.get();
        }
    }
}

void* TypeRegister::ResolveObject(ID id)
{
    if (resolver)
    {
        return resolver(id);
    }

    return nullptr;
}
