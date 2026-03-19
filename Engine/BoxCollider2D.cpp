#include "pch.h"
#include "BoxCollider2D.h"
#include "AssetManager.h"
#include "RenderManager.h"
#include "Mesh.h"
#include "Material.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "TMesh.h"
#include "VertexData.h"
#include "CircleCollider2D.h"
#include "RenderCommand.h"

void BoxCollider2D::Init()
{
	_mesh     = ASSET.Get<TMesh<VertexColliderData>>(L"Mesh_BoxCollider2D");
	_material = ASSET.Get<Material>(L"Material_Collider");

	RENDERER.AddCollider(shared_from_this());
	COLLISION.AddCollider(shared_from_this());
}

void BoxCollider2D::Start()
{
}

void BoxCollider2D::Update()
{
	Vector3 localScale    = _localTransform->GetLocalScale();
	Vector3 localPosition = _localTransform->GetLocalPosition();

	_min.x = localPosition.x - localScale.x / 2;
	_min.y = localPosition.y - localScale.y / 2;
	_max.x = localPosition.x + localScale.x / 2;
	_max.y = localPosition.y + localScale.y / 2;

	// AABB °»½Å
	_aabb.min = XMVector3TransformCoord(_min, Owner()->transform->GetWorldMatrix());
	_aabb.max = XMVector3TransformCoord(_max, Owner()->transform->GetWorldMatrix());

	_worldTransform->_worldMatrix = _localTransform->_worldMatrix * Owner()->transform->_worldMatrix;
}

bool BoxCollider2D::CheckCollision(const sptr<Collider>& target)
{
	if (auto box = std::dynamic_pointer_cast<BoxCollider2D>(target))
	{
		return BoxToBox(box);
	}
	else if (auto circle = std::dynamic_pointer_cast<CircleCollider2D>(target))
	{
		return BoxToCircle(circle);
	}
	else
	{
		return false;
	}
}

void BoxCollider2D::CollectDbgRenderData(RenderContext& ctx)
{
	DebugColliderRenderCommand cmd;
	{
		cmd.WorldMatrix = _worldTransform->GetWorldMatrix();
		cmd.Color       = Vector4(0.f, 1.f, 0.f, 1.f);
		cmd.Mesh        = _mesh;
		cmd.Material    = _material;
	}
	ctx.debugColliderCmds.push_back(cmd);
}

void BoxCollider2D::Offset(Vector3 offset)
{
	_localTransform->SetLocalPosition(offset);
}

void BoxCollider2D::Size(Vector3 scale)
{
	_localTransform->SetLocalScale(scale);
}

bool BoxCollider2D::BoxToBox(const sptr<BoxCollider2D>& target)
{
	AABB lhs = _aabb;
	AABB rhs = target->GetAABB();

	return max(lhs.min.x, rhs.min.x) < min(lhs.max.x, rhs.max.x) && max(lhs.min.y, rhs.min.y) < min(lhs.max.y, rhs.max.y);
}

bool BoxCollider2D::BoxToCircle(const sptr<class CircleCollider2D>& target)
{
	return false;
}
