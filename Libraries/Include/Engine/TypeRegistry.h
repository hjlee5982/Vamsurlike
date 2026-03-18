//#pragma once
//
//class TestComponent;
//
//class Field
//{
//public:
//    string name;
//    string typeName;
//
//    std::function<void(void*, nlohmann::json&)> serialize;
//    std::function<void(void*, const nlohmann::json&)> deserialize;
//
//    std::function<void* (void*)> getPtr;
//};
//
//class TypeInfo
//{
//public:
//    string typeName;
//    string parentName;
//
//    TypeInfo* parent = nullptr;
//
//    List<uptr<Field>> fields;
//};
//
//struct TypeData
//{
//    std::function<uptr<TestComponent>()> creator;
//    uptr<TypeInfo> typeInfo;
//};
//
//class TypeRegistry
//{
//public:
//    using CreateComponentFunc = uptr<TestComponent>(*)();
//public:
//    static void Register(const string& name, CreateComponentFunc func);
//    static uptr<TestComponent> Create(const string& name);
//    static uptr<TestComponent> Create1(const string& name);
//
//    static TypeInfo* RegisterType(const string& name, std::function<uptr<TestComponent>()> creator, const string& parentName);
//
//private:
//    static Dictionary<std::string, CreateComponentFunc>& GetDict();
//
//    static Dictionary<string, TypeData>& GetMap();
//
//public:
//    static TypeInfo* GetTypeInfo(const string& name);
//
//    static void SerializeType(void* obj, TypeInfo* type, nlohmann::json& json)
//    {
//        if (type->parent != nullptr)
//        {
//            SerializeType(obj, type->parent, json);
//        }
//
//        for (auto& field : type->fields)
//        {
//            field->serialize(obj, json);
//        }
//    }
//
//    static void DeserializeType(void* obj, TypeInfo* type, const nlohmann::json& json)
//    {
//        if (type->parent != nullptr)
//        {
//            DeserializeType(obj, type->parent, json);
//        }
//
//        for (auto& field : type->fields)
//        {
//            field->deserialize(obj, json);
//        }
//    }
//
//    static void ResolveParents()
//    {
//        auto& map = GetMap();
//
//        for (auto& [name, data] : map)
//        {
//            auto& type = data.typeInfo;
//
//            if (type->parentName.empty())
//            {
//                continue;
//            }
//
//            auto it = map.find(type->parentName);
//
//            if (it != map.end()) 
//            {
//                type->parent = it->second.typeInfo.get();
//            }
//        }
//    }
//
//    inline static std::function<void* (uint64_t)> resolver;
//    inline static std::function<void* (uint64_t)> componentResolver;
//
//    static void* ResolveObject(uint64_t id)
//    {
//        if (resolver)
//        {
//            return resolver(id);
//        }
//
//        return nullptr;
//    }
//    static void* ResolveComponent(uint64_t id)
//    {
//        if (componentResolver)
//        {
//            return componentResolver(id);
//        }
//
//        return nullptr;
//    }
//
//};
//
//template<typename Class, typename T>
//void RegisterField(TypeInfo* typeInfo, const string& name, T Class::* member)
//{
//    auto field = makeUptr<Field>();
//    field->name = name;
//    field->typeName = typeid(T).name();
//
//    field->serialize = [member, name](void* obj, nlohmann::json& json)
//        {
//            Class* c = static_cast<Class*>(obj);
//            json[name] = c->*member;
//        };
//
//    field->deserialize = [member, name](void* obj, const nlohmann::json& json)
//        {
//            if (json.contains(name) == false)
//            {
//                return;
//            }
//
//            Class* c = static_cast<Class*>(obj);
//            c->*member = json[name].get<T>();
//        };
//
//    typeInfo->fields.push_back(std::move(field));
//}
//
//template<typename Class, typename T>
//void RegisterObjectRef(TypeInfo* typeInfo, const string& name, T* Class::* member)
//{
//    auto field = makeUptr<Field>();
//    field->name = name;
//    field->typeName = typeid(T).name();
//
//    field->serialize = [member, name](void* obj, nlohmann::json& json)
//        {
//            Class* c = static_cast<Class*>(obj);
//
//            T* ptr = c->*member;
//
//            if (ptr)
//            {
//                json[name] = ptr->id;
//            }
//            else
//            {
//                json[name] = 0;
//            }
//        };
//
//    field->deserialize = [member, name](void* obj, const nlohmann::json& json)
//        {
//            if (!json.contains(name))
//            {
//                return;
//            }
//
//            Class* c = static_cast<Class*>(obj);
//
//            uint64_t id = json[name];
//
//            if (id == 0)
//            {
//                c->*member = nullptr;
//                return;
//            }
//
//            void* resolved = TypeRegistry::ResolveObject(id);
//
//            c->*member = static_cast<T*>(resolved);
//        };
//
//    typeInfo->fields.push_back(std::move(field));
//}