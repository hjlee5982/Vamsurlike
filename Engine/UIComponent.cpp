#include "pch.h"
#include "UIComponent.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "TMesh.h"
#include "Renderer.h"
#include "GameObject.h"

UIComponent::UIComponent()
{
    _debugMesh     = ASSET.Get<TMesh<VertexColliderData>>(L"Mesh_BoxCollider2D");
    _debugMaterial = ASSET.Get<Material>(L"Material_Collider");
}

sptr<TMesh<VertexUIData>> UIComponent::GetMesh()
{
    return _mesh;
}

sptr<Material> UIComponent::GetMaterial()
{
    return _material;
}

void UIComponent::SetMesh(sptr<TMesh<VertexUIData>> mesh)
{
    _mesh = mesh;
}

void UIComponent::SetTexture(const wstring& tag)
{
    _material->SetTexture(tag);
}

void UIComponent::SetMaterial(sptr<Material> material)
{
    _material = material;
}
