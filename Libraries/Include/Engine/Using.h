#pragma once

using f32 = float;
using f64 = double;

// #include<cstdint>
using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using string  = std::string;
using wstring = std::wstring;


#include "SimpleMath.h"
using Vector2    = DirectX::SimpleMath::Vector2;
using Vector3    = DirectX::SimpleMath::Vector3;
using Vector4    = DirectX::SimpleMath::Vector4;
using Matrix     = DirectX::SimpleMath::matx;
using Quaternion = DirectX::SimpleMath::Quaternion;
using Color      = DirectX::SimpleMath::Color;


// #include <memory>
template<typename T>
using sptr = std::shared_ptr<T>;
template<typename T>
using uptr = std::unique_ptr<T>;
template<typename T>
using wptr = std::weak_ptr<T>;


// #include <set>
// #include <unordered_set>
// #include <map>
// #include <unordered_map>

template<typename T>
using List = std::vector<T>;
template<typename T, typename Compare = std::less<Key>>
using SortedSet = std::set<T, Compare>;
template<typename T>
using HashSet = std::unordered_set<T>;
template<typename Key, typename Value, typename Compare = std::less<Key>>
using SortedDictionary = std::map<Key, Value, Compare>;
template<typename Key, typename Value>
using Dictionary = std::unordered_map<Key, Value>;

template<typename T, typename ...Args>
sptr<T> makeSptr(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T, typename ...Args>
uptr<T> makeUptr(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}
