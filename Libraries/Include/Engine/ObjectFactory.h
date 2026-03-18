#pragma once

#include "Object.h"
#include "IReflection.h"

struct PropertyInfo
{
	string name;
	size_t offset;

	std::function<void*(sptr<IReflection>)> getPtr;
	std::function<void(sptr<IReflection>, const string&)> fromString;
	std::function<string(sptr<IReflection>)> toString;
};



class ObjectFactory : public Singleton<ObjectFactory>
{
	using CreateFunc = std::function<sptr<IReflection>()>;
public:
	struct ObjectInfo
	{
		CreateFunc createFunc;
		List<PropertyInfo> properties;
	};
public:
	static Dictionary<string, ObjectInfo>& Registry()
	{
		static Dictionary<string, ObjectInfo> registry;
		return registry;
	}
	static void Register(const string& name, CreateFunc func)
	{
		Registry()[name].createFunc = func;
	}
	static void RegisterProperty(const string& name, const PropertyInfo& prop)
	{
		Registry()[name].properties.push_back(prop);
	}
	static sptr<IReflection> Create(const string& name)
	{
		auto it = Registry().find(name);
		
		if (it != Registry().end())
		{
			return it->second.createFunc();
		}

		return nullptr;
	}
public:
	virtual void Awake() override;
};



#define PROPERTY() \
inline static PropertyRegistrar __property_registrar_##__LINE__ = PropertyRegistrar(this, #__LINE__);


template<typename TClass, typename TField>
struct AutoPropertyRegister
{
	AutoPropertyRegister(const char* className, const char* fieldName, size_t offset)
	{
		PropertyInfo info;
		{
			info.name = fieldName;
			info.offset = offset;
			info.getPtr = [offset](Object* obj)
				{
					return reinterpret_cast<void*>(reinterpret_cast<char*>(obj) + offset);
				};
			info.toString = [offset](Object* obj)
				{
					TField* value = reinterpret_cast<TField*>(reinterpret_cast<char*>(obj) + offset);

					if constexpr (std::is_same_v<TField, string>)
					{
						return *value;
					}
					else
					{
						return std::to_string(*value);
					}
				};
			info.fromString = [offset](Object* obj, const string& str)
				{
					TField* value = reinterpret_cast<TField>(reinterpret_cast<char*>(obj) + offset);

					if constexpr (std::is_same_v<TField, int>)
					{
						*value = std::stoi(str);
					}
					else if constexpr (std::is_same_v<TField, float>)
					{
						*value = std::stof(str);
					}
					else if constexpr (std::is_same_v<TField, string>)
					{
						*value = str;
					}
				};
		}
		ObjectFactory::RegisterProperty(className, info);
	}
};



#define REFLECTION(T)															        \
public:																					\
	virtual const uint64_t  GetType() const override { return typeid(T).hash_code(); }	\
	virtual const char* GetTypeName() const override { return #T;}						\
private:																				\
	struct T##_RegisterHelper															\
	{																					\
		T##_RegisterHelper()															\
		{																				\
			ObjectFactory::Register(#T, []() {return makeSptr<T>();});					\
		}																				\
	};																					\
	inline static T##_RegisterHelper T##_regHelper;										\
																						\
	template<typename FieldType>														\
	struct PropertyRegister																\
	{																					\
		PropertyRegister(const char* fieldName, size_t offset)							\
		{																				\
			AutoPropertyRegister<T, FieldType>(#T, fieldName, offset);					\
		}																				\
	};																					\
using ThisClass = T;



#define PROPERTY_FIELD_(type, name, defaultValue)										\
type name = defaultValue;																\
inline static PropertyRegister<type> __reg_##name{ #name, offsetof(ThisClass, name)};