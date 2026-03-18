#pragma once

#include "Asset.h"

class Material : public Asset
{
public:
	Material() : Asset(EAssetType::Material) {}
public:
	virtual sptr<Asset> Clone() override;
public:
	void Bind();
public:
	sptr<class Shader> GetShader();
	sptr<class Texture> GetTexture();
public:
	void SetShader(sptr<class Shader> shader);
	void SetTexture(const wstring& tag);
	void SetTexture(sptr<class Texture> texture);
private:
	sptr<class Shader>  _shader;
	sptr<class Texture> _texture;
};

