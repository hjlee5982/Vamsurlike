#pragma once

#include "Component.h"

class TMeshBase;
class Material;
class Transform;

class Collider : public Component
{
public:
	Collider();
public:
	virtual bool CheckCollision(const sptr<Collider>& target) = 0;
	virtual void CollectDbgRenderData(struct RenderContext& ctx) = 0;
public:
	sptr<TMeshBase> GetMesh()      { return _mesh; }
	sptr<Material>  GetMaterial()  { return _material; }
	sptr<Transform> GetTransform() { return _worldTransform; }
protected:
	sptr<TMeshBase> _mesh;
	sptr<Material>  _material;
public:
	sptr<Transform> _worldTransform;
	sptr<Transform> _localTransform;
};

