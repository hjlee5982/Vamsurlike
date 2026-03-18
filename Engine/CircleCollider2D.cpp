#include "pch.h"
#include "CircleCollider2D.h"
#include "AssetManager.h"
#include "Transform.h"
#include "TMesh.h"
#include "Material.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include "BoxCollider2D.h"
#include "RenderCommand.h"

void CircleCollider2D::Init()
{
	_mesh     = ASSET.Get<TMesh<VertexColliderData>>(L"Mesh_CircleCollider2D");
	_material = ASSET.Get<Material>(L"Material_Collider");

	RENDERER.AddCollider(shared_from_this());
	COLLISION.AddCollider(shared_from_this());
}

void CircleCollider2D::Start()
{
}

void CircleCollider2D::Update()
{
	_center = XMVector3TransformCoord(_localTransform->GetLocalPosition(), Owner()->transform->GetWorldMatrix());
	_radius = (_localTransform->GetLocalScale().x * Owner()->transform->GetScale().x) / 2;

	_worldTransform->_worldMatrix = _localTransform->_worldMatrix * Owner()->transform->_worldMatrix;
}

bool CircleCollider2D::CheckCollision(const sptr<Collider>& target)
{
	if (auto box = std::dynamic_pointer_cast<BoxCollider2D>(target))
	{
		return box->CheckCollision(shared_from_this());
	}
	else if (auto circle = std::dynamic_pointer_cast<CircleCollider2D>(target))
	{
		return CircleToCircle(circle);
	}
	else
	{
		return false;
	}
}

void CircleCollider2D::CollectRenderData(RenderContext& ctx)
{
}

void CircleCollider2D::Offset(Vector3 offset)
{
	_localTransform->SetLocalPosition(offset);
}

void CircleCollider2D::Radius(f32 radius)
{
	_radius = radius;
	_localTransform->SetLocalScale(Vector3(_radius * 2, _radius * 2, _radius * 2));
}

bool CircleCollider2D::CircleToCircle(const sptr<class CircleCollider2D>& target)
{
	f32 distSq = (_center - target->_center).LengthSquared();
	f32 r = _radius + target->_radius;

	return distSq <= r * r;
}
