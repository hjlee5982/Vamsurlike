#pragma once

#include "Collider.h"

class CircleCollider2D : public Collider, public std::enable_shared_from_this<CircleCollider2D>
{
public:
	virtual void Init() override;
public:
	virtual void Start() override;
	virtual void Update() override;
public:
	virtual bool CheckCollision(const sptr<Collider>& target)    override;
	virtual void CollectDbgRenderData(struct RenderContext& ctx) override;
public:
	void Offset(Vector3 offset);
	void Radius(f32 radius);
private:
	bool CircleToCircle(const sptr<class CircleCollider2D>& target);
public:
	f32     _radius = 0.5f;
	Vector3 _center = Vector3::Zero;
};

