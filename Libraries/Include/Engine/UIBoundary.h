#pragma once

#include "Component.h"
#include "TMesh.h"

class Mesh;
class Material;
class Transform;

class UIBoundary : public Component, public std::enable_shared_from_this<UIBoundary>
{
public:
	virtual void Init() override;
public:
	sptr<TMesh<VertexColliderData>> GetMesh() { return _mesh; }
	sptr<Material>  GetMaterial()          { return _material;          }
	sptr<Transform> GetBoundaryTransform() { return _boundaryTransform; }
public:
	sptr<TMesh<VertexColliderData>>      _mesh;
	sptr<Material>  _material;
	sptr<Transform> _boundaryTransform;
};

