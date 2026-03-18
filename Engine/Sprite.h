#pragma once

class Sprite : public Asset
{
public:
	Sprite() : Asset(EAssetType::Sprite) {}
public:
	virtual void Load(const wstring& path) override {}
	virtual void Save(const wstring& path) override {}
public:
	void SetTexture(sptr<class Texture> texture);
private:
	wptr<class Texture> _texture;
};

