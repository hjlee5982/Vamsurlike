#include "pch.h"
#include "CollisionManager.h"
#include "BoxCollider2D.h"
#include "GameObject.h"
#include "Collider.h"

void CollisionManager::Awake()
{
}

void CollisionManager::FixedUpate()
{
	for (i32 i = 0; i < _colliders.size(); ++i)
	{
		auto c1 = _colliders[i].lock();

		if (c1 == nullptr || c1->Owner()->isActive == false)
		{
			continue;
		}
		else
		{
			for (i32 j = i + 1; j < _colliders.size(); ++j)
			{
				auto c2 = _colliders[j].lock();

				if (c2 == nullptr || c2->Owner()->isActive == false)
				{
					continue;
				}
				else
				{
					if (c1->CheckCollision(c2) == true)
					{
						c1->Owner()->OnCollisionEnter2D(c2);
						c2->Owner()->OnCollisionEnter2D(c1);
					}
				}
			}
		}
	}
}

void CollisionManager::AddCollider(sptr<Collider> collider)
{
	_colliders.push_back(collider);
}

