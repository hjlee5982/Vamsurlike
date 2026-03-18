#pragma once

using ID = uint64_t;

class Component;


class Field
{
public:
    string name;
    string typeName;

    std::function<void(void*, nlohmann::json&)>       serialize;
    std::function<void(void*, const nlohmann::json&)> deserialize;
};


class TypeInfo
{
public:
    string typeName;
    string parentName;

    TypeInfo* parent = nullptr;

    List<uptr<Field>> fields;
};


struct TypeData
{
    std::function<uptr<Component>()> creator;
    uptr<TypeInfo> typeInfo;
};


class TypeRegister
{
public:
    using CreateComponentFunc = uptr<Component>(*)();
public:
    static void            Register(const string& name, CreateComponentFunc func);
    static uptr<Component> CreateComponent(const string& name);
    static TypeInfo*       RegisterType(const string& name, std::function<uptr<Component>()> creator, const string& parentName);
private:
    static TypeInfo*                                GetTypeInfo(const string& name);
    static Dictionary<std::string, CreateComponentFunc>& GetCreator();
    static Dictionary<string, TypeData>&            GetTypeData();
public:
    static void SerializeType(void* obj, TypeInfo* type, nlohmann::json& json);
    static void DeserializeType(void* obj, TypeInfo* type, const nlohmann::json& json);
public:
    static void ResolveParents();
    static void* ResolveObject(ID id);
public:
    inline static std::function<void* (ID)> resolver;
};



template<typename Class, typename T>
void RegisterField(TypeInfo* typeInfo, const string& name, T Class::* member)
{
    auto field = makeUptr<Field>();
    field->name = name;
    field->typeName = typeid(T).name();

    field->serialize = [member, name](void* obj, nlohmann::json& json)
        {
            Class* c = static_cast<Class*>(obj);
            json[name] = c->*member;
        };

    field->deserialize = [member, name](void* obj, const nlohmann::json& json)
        {
            if (json.contains(name) == false)
            {
                return;
            }

            Class* c = static_cast<Class*>(obj);
            c->*member = json[name].get<T>();
        };

    typeInfo->fields.push_back(std::move(field));
}

template<typename Class, typename T>
void RegisterObjectRef(TypeInfo* typeInfo, const string& name, T* Class::* member)
{
    auto field = makeUptr<Field>();
    field->name = name;
    field->typeName = typeid(T).name();

    field->serialize = [member, name](void* obj, nlohmann::json& json)
        {
            Class* c = static_cast<Class*>(obj);

            T* ptr = c->*member;

            if (ptr)
            {
                json[name] = ptr->id;
            }
            else
            {
                json[name] = 0;
            }
        };

    field->deserialize = [member, name](void* obj, const nlohmann::json& json)
        {
            if (!json.contains(name))
            {
                return;
            }

            Class* c = static_cast<Class*>(obj);

            uint64_t id = json[name];

            if (id == 0)
            {
                c->*member = nullptr;
                return;
            }

            void* resolved = TypeRegister::ResolveObject(id);

            c->*member = static_cast<T*>(resolved);
        };

    typeInfo->fields.push_back(std::move(field));
}



#define ROOT_COMPONENT_BODY(TYPE)                 \
public:                                           \
    TYPE();                                       \
    virtual const char* GetTypeName() const       \
    {                                             \
        return GetTypeNameStatic();               \
    }                                             \
    static const char* GetTypeNameStatic()        \
    {                                             \
        return #TYPE;                             \
    }                                             \
    static std::unique_ptr<Component> Create()    \
    {                                             \
        return std::make_unique<TYPE>();          \
    }                                             \


#define COMPONENT_BODY(TYPE)                      \
public:                                           \
    using Super = SUPER;                          \
public:                                           \
    TYPE();                                       \
    virtual const char* GetTypeName() const       \
    {                                             \
        return GetTypeNameStatic();               \
    }                                             \
    static const char* GetTypeNameStatic()        \
    {                                             \
        return #TYPE;                             \
    }                                             \
    static std::unique_ptr<Component> Create()    \
    {                                             \
        return std::make_unique<TYPE>();          \
    }                                             \


#define ROOT_COMPONENT_IMPL                                                              \
TYPE::TYPE() {}                                                                          \
static bool TYPE##_TypeInit = []()                                                       \
    {                                                                                    \
        TypeInfo* typeInfo = TypeRegister::RegisterType                                  \
        (TYPE::GetTypeNameStatic(), &TYPE::Create, "");                                  \
                                                                                         \
        TYPE::RegisterFields(typeInfo);                                                  \
                                                                                         \
        return true;                                                                     \
    }();                                                                                 \


#define COMPONENT_IMPL                                                                   \
TYPE::TYPE() {}                                                                          \
static bool TYPE##_TypeInit = []()                                                       \
    {                                                                                    \
        TypeInfo* typeInfo = TypeRegister::RegisterType                                  \
        (TYPE::GetTypeNameStatic(), &TYPE::Create, TYPE::Super::GetTypeNameStatic());    \
                                                                                         \
        TYPE::RegisterFields(typeInfo);                                                  \
                                                                                         \
        return true;                                                                     \
    }();                                                                                 \


#define REGISTER_FIELD(TYPE, FIELD)                        \
RegisterField<TYPE>(typeInfo, #FIELD, &TYPE::FIELD);       \

#define REGISTER_OBJECT_REF(CLASS, FIELD)                  \
RegisterObjectRef<CLASS>(typeInfo, #FIELD, &CLASS::FIELD)  \

#define PROPERTY_FIELD                                     \
static void RegisterFields(TypeInfo* typeInfo)             \