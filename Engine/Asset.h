#pragma once

enum class EAssetType : i8
{
	None = -1,
	Mesh,
	Texture,
	Material,
	Shader,
	AnimationClip,
	Sprite,
	TMesh,

	End
};

enum
{
	Asset_Type_Count = static_cast<i8>(EAssetType::End)
};

class Asset abstract
{
public:
	Asset(EAssetType type) : _assetType(type) {}
public:
	virtual void Load(const wstring& path) {};
	virtual void Save(const wstring& path) {};
public:
	virtual sptr<Asset> Clone() { return nullptr; };
public:
	EAssetType GetAssetType()
	{
		return _assetType;
	}
protected:
	EAssetType _assetType = EAssetType::None;
public:
	wstring _tag;
	wstring _path;
};

