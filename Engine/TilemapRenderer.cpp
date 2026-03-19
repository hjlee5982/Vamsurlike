#include "pch.h"
#include "TilemapRenderer.h"

#include "AssetManager.h"
#include "RenderManager.h"
#include "TMesh.h"
#include "Material.h"
#include "Tilemap.h"

void TilemapRenderer::Init()
{
	// 그리드
	_mesh     = ASSET.Get<TMesh<VertexTextureData>>(L"Mesh_Grid");
	_dbgMaterial = ASSET.Get<Material>(L"Material_Default");
	_dbgMaterial->SetTexture(L"Texture_Square");

	// 타일맵
	_tileMesh = makeSptr<TMesh<VertexTextureData>>();
	_geometry = makeSptr<Geometry<VertexTextureData>>();
	_material = ASSET.Clone<Material>(L"Material_Default");

	RENDERER.AddRenderer(shared_from_this());
	RENDERER.AddDbgRenderer(shared_from_this());
}

void TilemapRenderer::CollectRenderData(RenderContext& ctx)
{
	// 타일맵 랜더링
	TilemapRenderCommand cmd;
	{
		cmd.WorldMatrix  = Owner()->transform->GetWorldMatrix();
		cmd.Mesh         = _tileMesh;
		cmd.Material     = _material;
		cmd.OrderInLayer = OrderInLayer;
	}
	ctx.tilemapCmds.push_back(cmd);
}

void TilemapRenderer::CollectDbgRenderData(RenderContext& ctx)
{
	if (Grid)
	{
		// 그리드 랜더링
		DebugObjectRenderCommand dbg;
		{
			dbg.WorldMatrix = Owner()->transform->GetWorldMatrix();
			dbg.Mesh = _mesh;
			dbg.Material = _dbgMaterial;
			dbg.OrderInLayer = OrderInLayer;
		}
		ctx.debugObjectCmds.push_back(dbg);
	}
}

void TilemapRenderer::SetTilemap(sptr<class Tilemap> tilemap)
{
	_material->SetTexture(tilemap->_texture);

	_geometry->SetVertices(tilemap->vtx);
	_geometry->SetIndices(tilemap->idx);

	_tileMesh->CreateMesh(_geometry);
}
