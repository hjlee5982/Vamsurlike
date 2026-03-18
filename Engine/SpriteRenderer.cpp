#include "pch.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Material.h"
#include "RenderManager.h"
#include "Texture.h"
#include "TMesh.h"
#include "Transform.h"
#include "RenderCommand.h"

void SpriteRenderer::Init()
{
	_mesh     = ASSET.Get<TMesh<VertexTextureData>>(L"Mesh_Square");
	_material = ASSET.Clone<Material>(L"Material_Default");

	RENDERER.AddRenderer(shared_from_this());
}

void SpriteRenderer::CollectRenderData(RenderContext& ctx)
{
	SpriteRenderCommand cmd;
	{
		cmd.WorldMatrix  = Owner()->transform->GetWorldMatrix();
		cmd.Mesh         = _mesh;
		cmd.Material     = _material;
		cmd.OrderInLayer = OrderInLayer;
	}
	ctx.spriteCmds.push_back(cmd);
}