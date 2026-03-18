#include "pch.h"
#include "TilemapRenderer.h"

#include "AssetManager.h"
#include "RenderManager.h"
#include "TMesh.h"
#include "Material.h"
#include "Tilemap.h"

void TilemapRenderer::Init()
{
	_mesh     = ASSET.Get<TMesh<VertexTextureData>>(L"Mesh_Grid");

	_tileMesh = makeSptr<TMesh<VertexTextureData>>();
	_geometry = makeSptr<Geometry<VertexTextureData>>();
	_material = ASSET.Clone<Material>(L"Material_Default");

	RENDERER.AddRenderer(shared_from_this());
}

void TilemapRenderer::CollectRenderData(RenderContext& ctx)
{
	TilemapRenderCommand cmd;
	{
		cmd.WorldMatrix  = Owner()->transform->GetWorldMatrix();
		cmd.Mesh         = _tileMesh;
		cmd.Material     = _material;
		cmd.OrderInLayer = OrderInLayer;
	}
	ctx.tilemapCmds.push_back(cmd);
}

void TilemapRenderer::SetTilemap(sptr<class Tilemap> tilemap)
{
	_material->SetTexture(tilemap->_texture);

	_geometry->SetVertices(tilemap->vtx);
	_geometry->SetIndices(tilemap->idx);

	_tileMesh->CreateMesh(_geometry);
}
