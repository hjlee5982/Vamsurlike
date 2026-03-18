#pragma once

#include "Component.h"

enum class ProjectionType
{
	Perspective,
	Orthogonal,
	OrthoUI
};

struct CameraDesc
{
	ProjectionType Type;
	f32 Near;
	f32 Far;
	f32 OrthoSize;
};

class Camera : public Component
{
public:
	void Initialize(CameraDesc desc);
public:
	virtual void Update()     override;
public:
	f32 GetNear() { return _near; }
	f32 GetFar()  { return _far;  }
	f32 GetFov()  { return _fov;  }
public:
	void SetNear(f32 Near) { _near = Near; }
	void SetFar(f32 Far)   { _far  = Far;  }
	void SetFov(f32 fov)   { _fov  = fov;  }
private:
	ProjectionType _type;
	f32 _near;
	f32 _far;
	f32 _fov;
	f32 _orthoSize;
};

