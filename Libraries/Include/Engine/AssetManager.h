#pragma once

#include "Asset.h"
#include "TMesh.h"

class Mesh;
class Shader;
class Texture;
class Material;

class AssetManager : public Singleton<AssetManager>
{
public:
	virtual void Awake() override;
public:
	template<typename T>
	bool Add(const wstring& key, sptr<T> object);

	template<typename T>
	sptr<T> Load(const wstring& key, const wstring& path);

	template<typename T>
	sptr<T> Get(const wstring& key);

	template<typename T>
	sptr<T> Clone(const wstring& key);

	template<typename T>
	EAssetType GetAssetType();
	// 생성 요청 함수
public:
	void LoadTexture(const wstring& tag, const wstring& path);
private:
	// 엔진에서 사용될 기본 에셋들을 생성
	void CreateDefaultShader();
	void CreateDefaultMesh();
	void CreateDefaultTexture();
	void CreateDefaultMaterial();
private:
	using KeyAssetPair = Dictionary<wstring, sptr<Asset>>;
	std::array<KeyAssetPair, Asset_Type_Count> _resources;
};

template<typename T>
inline bool AssetManager::Add(const wstring& key, sptr<T> object)
{
	EAssetType assetType = GetAssetType<T>();
	KeyAssetPair& kap = _resources[static_cast<int>(assetType)];

	auto it = kap.find(key);

	if (it != kap.end())
	{
		return false;
	}

	kap[key] = object;

	return true;
}

template<typename T>
inline sptr<T> AssetManager::Load(const wstring& key, const wstring& path)
{
	EAssetType assetType = GetAssetType<T>();
	KeyAssetPair& kap = _resources[static_cast<int>(assetType)];

	auto it = kap.find(key);

	if (it != kap.end())
	{
		return std::static_pointer_cast<T>(it->second);
	}

	sptr<T> obj = makeSptr<T>();
	obj->Load(path);
	kap[key] = obj;

	return obj;
}

template<typename T>
inline sptr<T> AssetManager::Get(const wstring& key)
{
	EAssetType assetType = GetAssetType<T>();
	KeyAssetPair& kap = _resources[static_cast<int>(assetType)];

	auto it = kap.find(key);

	if (it != kap.end())
	{
		return std::static_pointer_cast<T>(it->second);
	}

	return nullptr;
}

template<typename T>
inline sptr<T> AssetManager::Clone(const wstring& key)
{
	EAssetType assetType = GetAssetType<T>();
	KeyAssetPair& kap = _resources[static_cast<int>(assetType)];

	auto it = kap.find(key);

	if (it != kap.end())
	{
		auto asset = it->second->Clone();

		return std::static_pointer_cast<T>(asset);
	}

	return nullptr;
}

template<typename T>
inline EAssetType AssetManager::GetAssetType()
{
	if (std::is_same_v<T, Texture>)
	{
		return EAssetType::Texture;
	}
	if (std::is_same_v<T, Mesh>)
	{
		return EAssetType::Mesh;
	}
	if (std::is_same_v<T, Material>)
	{
		return EAssetType::Material;
	}
	if (std::is_same_v<T, Shader>)
	{
		return EAssetType::Shader;
	}
	
	if constexpr (std::is_base_of_v<TMeshBase, T>)
	{
		return EAssetType::TMesh;
	}

	return EAssetType::None;
}
