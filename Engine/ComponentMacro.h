//#pragma once
//#include "TypeRegistry.h"
//
//#define ROOT_COMPONENT_BODY(TYPE) \
//public:\
//    TYPE();\
//    static const char* StaticTypeName() { return #TYPE; } \
//    virtual const char* GetTypeName() const { return StaticTypeName(); } \
//    static TypeInfo* GetStaticTypeInfo(); \
//    static std::unique_ptr<TestComponent> CreateInstance() { return std::make_unique<TYPE>(); } \
//
//#define COMPONENT_BODY(TYPE, SUPER) \
//public:\
//    using Super = SUPER;\
//    TYPE();\
//    static const char* StaticTypeName() { return #TYPE; } \
//    virtual const char* GetTypeName() const override { return StaticTypeName(); } \
//    static TypeInfo* GetStaticTypeInfo(); \
//    static std::unique_ptr<TestComponent> CreateInstance() { return std::make_unique<TYPE>(); } \
//
//#define ROOT_COMPONENT_IMPL(TYPE) \
//TYPE::TYPE(){}\
//static bool TYPE##_TypeInit = []()\
//{\
//    TypeInfo* type = TypeRegistry::RegisterType(        TYPE::StaticTypeName(),        &TYPE::CreateInstance,        "" );\
//\
//    TYPE::RegisterFields(type);\
//\
//    return true;\
//}();
//
//#define COMPONENT_IMPL(TYPE) \
//TYPE::TYPE(){}\
//\
//static bool TYPE##_TypeInit = []()\
//{\
//    TypeInfo* type = TypeRegistry::RegisterType(TYPE::StaticTypeName(), &TYPE::CreateInstance, TYPE::Super::StaticTypeName());\
//    TYPE::RegisterFields(type);\
//    return true;\
//}();
//
//#define REGISTER_FIELD(TYPE, FIELD) \
//RegisterField<TYPE>(type, #FIELD, &TYPE::FIELD);
//
//#define REGISTER_OBJECT_REF(CLASS, FIELD) \
//RegisterObjectRef<CLASS>(type, #FIELD, &CLASS::FIELD)
//
//
//#define PROPERTY_FIELD static void RegisterFields(TypeInfo* type)