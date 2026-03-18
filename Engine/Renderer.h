#pragma once

#include "Component.h"

class Mesh;
class Texture;
class Material;
class TMeshBase;

enum class RenderQueue
{
	Opaque      = 2000,
	AlphaTest   = 2450,
	Transparent = 3000,
	Overlay     = 4000
};

class Renderer : public Component
{
public:
	virtual void CollectRenderData(struct RenderContext& ctx) = 0;
public:
	sptr<TMeshBase> GetMesh();
	sptr<Material>  GetMaterial();
public:
	void SetMesh(sptr<TMeshBase> mesh);
	void SetTexture(const wstring& tag);
	void SetMaterial(sptr<Material> material);
protected:
	sptr<TMeshBase> _mesh;
	sptr<Material>  _material;
};

