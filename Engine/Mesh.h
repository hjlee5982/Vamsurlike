#pragma once

#include "Asset.h"
#include "Geometry.h"
#include "VertexData.h"

class IndexBuffer;
class VertexBuffer;

enum class EMeshType
{
	Square,
	Cube,
	Sphere,

	BoxCollider2D,

	Font,

	End
};

class Mesh : public Asset
{
public:
	Mesh() : Asset(EAssetType::Mesh) {}
public:
	void CreateMesh(EMeshType type);
	void CreateMesh(sptr<Geometry<VertexTextureData>> geometry);
	void Bind();
private:
	void CreateBuffers();
public:
	sptr<VertexBuffer>                GetVertexBuffer();
	sptr<IndexBuffer>                 GetIndexBuffer();
	sptr<Geometry<VertexTextureData>> GetGeometry();
private:
	sptr<VertexBuffer>                _vertexBuffer;
	sptr<IndexBuffer>                 _indexBuffer;
	sptr<Geometry<VertexTextureData>> _geometry;
};