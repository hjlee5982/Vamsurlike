#include "pch.h"
#include "Transform.h"
#include "GameObject.h"

//void Transform::MakeJson()
//{
//	_json["Type"] = GetTypeName();
//
//	_json["LocalMatrix"]   = _localMatrix;
//	_json["WorldMatrix"]   = _worldMatrix;
//	_json["Position"]      = _position;
//	_json["Scale"]         = _scale;
//	_json["Rotation"]      = _rotation;
//	_json["Right"]         = _right;
//	_json["Up"]            = _up;
//	_json["Look"]          = _look;
//}
//
//void Transform::LoadJson(const nlohmann::json& json)
//{
//	_look          = json["Data"]["Look"];
//	_localMatrix   = json["Data"]["LocalMatrix"];
//	_worldMatrix   = json["Data"]["WorldMatrix"];
//	_position	   = json["Data"]["Position"];
//	_scale		   = json["Data"]["Scale"];
//	_rotation	   = json["Data"]["Rotation"];
//	_right		   = json["Data"]["Right"];
//	_up			   = json["Data"]["Up"];
//}

void Transform::Update()
{
	Matrix scale    = Matrix::CreateScale         (_localScale);
	Matrix rotation = Matrix::CreateFromQuaternion(_localRotation);
	Matrix position = Matrix::CreateTranslation   (_localPosition);

	_localMatrix = scale * rotation * position;

	if (_parent.lock() != nullptr)
	{
		_worldMatrix = _localMatrix * _parent.lock()->GetWorldMatrix();
	}
	else
	{
		_worldMatrix = _localMatrix;
	}

	XMVECTOR S, R, T;
	::XMMatrixDecompose(&S, &R, &T, _worldMatrix);
	{
		_scale    = Vector3(S);
		_rotation = Quaternion(R);
		_position = Vector3(T);
	}

	for (auto& child : _children)
	{
		child->Update();
	}
}

void Transform::SetPosition(const Vector3& worldPosition)
{
	if (_parent.lock() != nullptr)
	{
		Matrix parentWorldMatrixInverse = _parent.lock()->GetWorldMatrix().Invert();

		Vector3 localPosision = ::XMVector3TransformCoord(worldPosition, parentWorldMatrixInverse);

		SetLocalPosition(localPosision);
	}
	else
	{
		SetLocalPosition(worldPosition);
	}
}

void Transform::SetScale(const Vector3& worldScale)
{
	if (_parent.lock() != nullptr)
	{
		Vector3 parentScale = _parent.lock()->GetScale();

		Vector3 localScale = worldScale / parentScale;

		SetLocalScale(localScale);
	}
	else
	{
		SetLocalScale(worldScale);
	}
}

void Transform::SetRotation(const Quaternion& worldRotation)
{
	if (_parent.lock() != nullptr)
	{
		Quaternion parentWorldRotationInverse = ::XMQuaternionInverse(_parent.lock()->GetRotation());

		Quaternion localRotation = ::XMQuaternionMultiply(parentWorldRotationInverse, worldRotation);

		SetLocalRotation(localRotation);
	}
	else
	{
		SetLocalRotation(worldRotation);
	}
}

void Transform::Translation(const Vector3& dir, float speed)
{
	_localPosition += dir * speed;
	Update();
}

sptr<Transform> Transform::GetChild(i32 index)
{
	if (_children.size() == 0 || _children.size() < index)
	{
		return nullptr;
	}

	return _children[index];
}

void Transform::SetParent(sptr<Transform> parent)
{
	if (_parent.lock() != nullptr)
	{
		auto& siblings = _parent.lock()->_children;

		auto it = std::find_if(siblings.begin(), siblings.end(), [this]
		(const sptr<Transform>& child)
			{
				return child.get() == this;
			});

		if (it != siblings.end())
		{
			siblings.erase(it);
		}
	}

	_parent = parent;

	if (parent != nullptr)
	{
		parent->_children.push_back(shared_from_this());
	}
}

void Transform::SetActive(bool active)
{
	for (auto& transform : _children)
	{
		if (transform->Owner() != nullptr)
		{
			transform->Owner()->SetActive(active);
		}
	}
}