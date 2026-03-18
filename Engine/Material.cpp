#include "pch.h"
#include "Material.h"
#include "Texture.h"
#include "Shader.h"
#include "Sprite.h"
#include "AssetManager.h"

sptr<Asset> Material::Clone()
{
	auto material = makeSptr<Material>(*this);
	{
		material->SetTexture(L"Texture_Default");
	}

	return material;
}

void Material::Bind()
{
	_shader->Bind();

	if (_texture != nullptr)
	{
		CONTEXT->PSSetShaderResources(0, 1, _texture->GetSRV().GetAddressOf());
	}
}

sptr<class Shader> Material::GetShader()
{
	return _shader;
}

sptr<class Texture> Material::GetTexture()
{
	return _texture;
}

void Material::SetShader(sptr<class Shader> shader)
{
	_shader = shader;
}

void Material::SetTexture(const wstring& tag)
{
	auto texture = ASSET.Get<Texture>(tag);

	if (texture != nullptr)
	{
		_texture = texture;
	}
	else
	{
		_texture = ASSET.Get<Texture>(L"Texture_Default");
	}
}

void Material::SetTexture(sptr<class Texture> texture)
{
	_texture = texture;
}
