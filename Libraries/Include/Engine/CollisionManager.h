#pragma once

class CollisionManager : public Singleton<CollisionManager>
{
public:
	virtual void Awake() override;
public:
	void FixedUpate();
public:
	void AddCollider(sptr<class Collider> collider);
private:
	List<wptr<class Collider>> _colliders;
};

