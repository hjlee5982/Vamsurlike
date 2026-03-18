//#include "pch.h"
//#include "TypeRegistry.h"
//#include "TestComponent.h"
//
//std::unordered_map<std::string, TypeRegistry::CreateComponentFunc>& TypeRegistry::GetDict()
//{
//    static std::unordered_map<std::string, CreateComponentFunc> dict;
//
//    return dict;
//}
//
//Dictionary<string, TypeData>& TypeRegistry::GetMap()
//{
//    static Dictionary<string, TypeData> map;
//
//    return map;
//}
//
//TypeInfo* TypeRegistry::GetTypeInfo(const string& name)
//{
//    auto& map = GetMap();
//
//    auto it = map.find(name);
//
//    if (it == map.end())
//    {
//        return nullptr;
//    }
//
//    return it->second.typeInfo.get();
//}
//
//void TypeRegistry::Register(const std::string& name, CreateComponentFunc func)
//{
//    GetDict()[name] = func;
//}
//
//uptr<TestComponent> TypeRegistry::Create(const std::string& name)
//{
//    auto& dict = GetDict();
//
//    auto it = dict.find(name);
//
//    if (it == dict.end())
//    {
//        return nullptr;
//    }
//
//    return it->second();
//}
//
//uptr<TestComponent> TypeRegistry::Create1(const string& name)
//{
//    auto& dict = GetMap();
//
//    auto it = dict.find(name);
//
//    if (it == dict.end())
//    {
//        return nullptr;
//    }
//
//    return it->second.creator();
//}
//
//TypeInfo* TypeRegistry::RegisterType(const string& name, std::function<uptr<TestComponent>()> creator, const string& parentName)
//{
//    auto& map = GetMap();
//
//    TypeData data;
//    data.creator = creator;
//    data.typeInfo = makeUptr<TypeInfo>();
//    data.typeInfo->typeName = name;
//    data.typeInfo->parentName = parentName;
//
//    map[name] = std::move(data);
//
//    return map[name].typeInfo.get();
//}