#include "pch.h"
#include "Renderer.h"
#include "TMesh.h"
#include "Material.h"
#include "Texture.h"

sptr<TMeshBase> Renderer::GetMesh()
{
	return _mesh;
}

sptr<Material> Renderer::GetMaterial()
{
	return _material;
}

void Renderer::SetMesh(sptr<TMeshBase> mesh)
{
	_mesh = mesh;
}

void Renderer::SetTexture(const wstring& tag)
{
	_material->SetTexture(tag);
}

void Renderer::SetMaterial(sptr<Material> material)
{
	_material = material;
}
