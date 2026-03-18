#include "pch.h"
#include "TestComponent.h"
#include "TypeRegistry.h"

ROOT_COMPONENT_IMPL(TestComponent)

void TestComponent::MakeJson(nlohmann::json& json) const
{
	json["type"] = GetTypeName();

	TypeInfo* type = TypeRegistry::GetTypeInfo(GetTypeName());

	TypeRegistry::SerializeType((void*)this, type, json);
}

void TestComponent::LoadJson(const nlohmann::json& json)
{
	TypeInfo* type = TypeRegistry::GetTypeInfo(GetTypeName());

	TypeRegistry::DeserializeType(this, type, json);
}