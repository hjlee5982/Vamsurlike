#pragma once

#include "Struct.h"

class IJson abstract
{
public:
	virtual nlohmann::json MakeJson() {};
	virtual void LoadJson(const nlohmann::json& json) {};
public:
	nlohmann::json _json;
};

namespace nlohmann
{
	// Vector3
	template<>
	struct adl_serializer<DirectX::SimpleMath::Vector3>
	{
		// Vector3
		static void to_json(json& j, const DirectX::SimpleMath::Vector3& v)
		{
			j = json{ {"x", v.x}, {"y", v.y}, {"z", v.z} };
		}
		static void from_json(const json& j, DirectX::SimpleMath::Vector3& v)
		{
			v.x = j.at("x").get<float>();
			v.y = j.at("y").get<float>();
			v.z = j.at("z").get<float>();
		}
		
		// Quaternion
		static void to_json(json& j, const DirectX::SimpleMath::Quaternion& q)
		{
			j = json{ {"x", q.x}, {"y", q.y}, {"z", q.z}, {"w", q.w} };
		}
		static void from_json(const json& j, DirectX::SimpleMath::Quaternion& q)
		{
			q.x = j.at("x").get<float>();
			q.y = j.at("y").get<float>();
			q.z = j.at("z").get<float>();
			q.w = j.at("w").get<float>();
		}
	};
	// Matrix
	template<>
	struct adl_serializer<DirectX::SimpleMath::matx>
	{
		static void to_json(json& j, const DirectX::SimpleMath::matx& m)
		{
			j = json::array();

			for (int i = 0; i < 4; ++i)
			{
				for (int k = 0; k < 4; ++k)
				{
					j.push_back(m.m[i][k]);
				}
			}
		}
		static void from_json(const json& j, DirectX::SimpleMath::matx& m)
		{
			for (int i = 0; i < 4; ++i)
			{
				for (int k = 0; k < 4; ++k)
				{
					m.m[i][k] = j[i * 4 + k].get<float>();
				}
			}
		}
	};
	// Quaternion
	template<>
	struct adl_serializer<DirectX::SimpleMath::Quaternion>
	{
		// Quaternion
		static void to_json(json& j, const DirectX::SimpleMath::Quaternion& q)
		{
			j = json{ {"x", q.x}, {"y", q.y}, {"z", q.z}, {"w", q.w} };
		}
		static void from_json(const json& j, DirectX::SimpleMath::Quaternion& q)
		{
			q.x = j.at("x").get<float>();
			q.y = j.at("y").get<float>();
			q.z = j.at("z").get<float>();
			q.w = j.at("w").get<float>();
		}
	};

	template<>
	struct adl_serializer<TestDesc>
	{
		static void to_json(json& j, const TestDesc& s)
		{
			j = json{ {"a", s.a}, {"b", s.b} };
		}
		static void from_json(const json& j, TestDesc& s)
		{
			s.a = j.at("a").get<int>();
			s.b = j.at("b").get<float>();
		}
	};
}