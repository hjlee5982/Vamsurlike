#pragma once

#include "Renderer.h"
#include "Geometry.h"
#include "VertexData.h"
#include "TMesh.h"

class TilemapRenderer : public Renderer, public std::enable_shared_from_this<TilemapRenderer>
{
public:
	virtual void Init() override;
public:
	virtual void CollectRenderData(RenderContext& ctx) override;
public:
	void SetTilemap(sptr<class Tilemap> tilemap);
private:
	sptr<Geometry<VertexTextureData>> _geometry;
	sptr<TMesh<VertexTextureData>>    _tileMesh;
public:
	i32 OrderInLayer = 0;
};

