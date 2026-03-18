#include "pch.h"
#include "Component.h"

void Component::SetOwner(sptr<class GameObject> owner)
{
	gameObject = owner;
}

sptr<GameObject> Component::Owner()
{
	return gameObject.lock();
}