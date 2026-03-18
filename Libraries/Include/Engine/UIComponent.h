#pragma once

#include "Component.h"
#include "VertexData.h"
#include "TMesh.h"

class Texture;
class Material;

class UIComponent : public Component
{
public:
	UIComponent();
public:
	virtual void CollectRenderData(struct RenderContext& ctx) = 0;
public:
	sptr<TMesh<VertexUIData>> GetMesh();
	sptr<Material>            GetMaterial();
public:
	void SetMesh(sptr<TMesh<VertexUIData>> mesh);
	void SetTexture(const wstring& tag);
	void SetMaterial(sptr<Material> material);
public:
	Vector4 color = { 1.f, 1.f, 1.f, 1.f };
protected:
	sptr<TMesh<VertexUIData>> _mesh;
	sptr<Material>            _material;
public:
	sptr<TMesh<VertexColliderData>> GetDebugMesh()
	{
		return _debugMesh;
	}
	sptr<Material> GetDebugMaterial()
	{
		return _debugMaterial;
	}
protected:
	Vector4							_debugColor = Vector4(0.5f, 0.5f, 0.5f, 1.f);
	sptr<TMesh<VertexColliderData>> _debugMesh;
	sptr<Material>					_debugMaterial;
};

