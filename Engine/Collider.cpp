#include "pch.h"
#include "Collider.h"

Collider::Collider()
{
	_worldTransform = makeSptr<Transform>();
	_localTransform = makeSptr<Transform>();
}