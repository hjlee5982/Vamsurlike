#include "pch.h"
#include "Camera.h"
#include "Transform.h"
#include "GameObject.h"

void Camera::Initialize(CameraDesc desc)
{
	_type      = desc.Type;
	_near      = desc.Near;
	_far       = desc.Far;
	_fov       = ::XMConvertToRadians(60.f);
	_orthoSize = desc.OrthoSize;

	switch (_type)
	{
	case ProjectionType::Perspective:

		Owner()->transform->SetPosition(Vector3(0.f, 0.f, -_far / 2));
		break;

	case ProjectionType::Orthogonal:

		Owner()->transform->SetPosition(Vector3(0.f, 0.f, -_far / 2));
		break;

	case ProjectionType::OrthoUI:

		Owner()->transform->SetPosition(Vector3(0.f, 0.f, -10.f));
		break;
	}
}

void Camera::Update()
{
	switch (_type)
	{
	case ProjectionType::Perspective:

		Global::ViewMatrix = Owner()->transform->GetWorldMatrix().Invert();
		Global::ProjMatrix = ::XMMatrixPerspectiveFovLH(_fov, Global::Aspect(), _near, _far);
		break;


	case ProjectionType::Orthogonal:
	{
		Global::ViewMatrix = Owner()->transform->GetWorldMatrix().Invert();
		Global::ProjMatrix = ::XMMatrixOrthographicLH(_orthoSize * Global::Aspect() * 2, _orthoSize * 2, _near, _far);
		break;
	}
	case ProjectionType::OrthoUI:

		Global::UIViewMatrix = Matrix::Identity;
		Global::UIProjMatrix = ::XMMatrixOrthographicLH(Global::ClientOption.width, Global::ClientOption.height, 0, 1);
		break;
	}
}