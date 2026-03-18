#pragma once

#include "Asset.h"
#include "Geometry.h"
#include "GeometryHelper.h"
#include "VertexData.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

enum class ETMeshType
{
	Square,
	Circle,
	Cube,
	Sphere,
	Grid,

	End
};


class TMeshBase : public Asset
{
public:
	TMeshBase() : Asset(EAssetType::Mesh) {}
public:
	virtual void Bind(sptr<Shader> shader) = 0;
};

template<typename T>
class TMesh : public TMeshBase
{
public:
	TMesh<T>() : TMeshBase() {}
public:
	void CreateMesh(ETMeshType type);
	void CreateMesh(sptr<Geometry<T>> geometry);
	virtual void Bind(sptr<Shader> shader) override;
private:
	sptr<class VertexBuffer> _vertexBuffer;
	sptr<class IndexBuffer>  _indexBuffer;
private:
	Dictionary<size_t, ComPtr<ID3D11InputLayout>> _inputLayouts;
private:
	sptr<Geometry<T>>  _geometry;
};

template<typename T>
inline void TMesh<T>::CreateMesh(ETMeshType type)
{
	_geometry = makeSptr<Geometry<T>>();

	switch (type)
	{
	case ETMeshType::Square:
		GeometryHelper::CreateSquare(_geometry);
		break;

	case ETMeshType::Circle:
		GeometryHelper::CreateCircle(_geometry);
		break;

	case ETMeshType::Cube:
		GeometryHelper::CreateCube(_geometry);
		break;

	case ETMeshType::Sphere:
		GeometryHelper::CreateSphere(_geometry);
		break;
		
	case ETMeshType::Grid:
		GeometryHelper::CreateGrid(_geometry);

	default:
		break;
	}

	_vertexBuffer = makeSptr<VertexBuffer>();
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = makeSptr<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());
}

template<typename T>
inline void TMesh<T>::CreateMesh(sptr<Geometry<T>> geometry)
{
	_vertexBuffer = makeSptr<VertexBuffer>();
	_vertexBuffer->Create(geometry->GetVertices());

	_indexBuffer = makeSptr<IndexBuffer>();
	_indexBuffer->Create(geometry->GetIndices());
}

template<typename T>
inline void TMesh<T>::Bind(sptr<Shader> shader)
{
	auto id = typeid(T).hash_code();

	if (_inputLayouts.find(id) == _inputLayouts.end())
	{
		ComPtr<ID3D11InputLayout> inputLayout;

		auto desc          = T::GetInputLayoutDesc();
		auto bufferPointer = shader->GetVSByteCode()->GetBufferPointer();
		auto bufferSize    = shader->GetVSByteCode()->GetBufferSize();

		auto hr = DEVICE->CreateInputLayout(desc.data(), desc.size(), bufferPointer, bufferSize, inputLayout.GetAddressOf());
	
		_inputLayouts[id] = inputLayout;
	}

	CONTEXT->IASetInputLayout(_inputLayouts[id].Get());

	_vertexBuffer->PushData();
	_indexBuffer->PushData();

	CONTEXT->DrawIndexed(_indexBuffer->GetIndexCount(), 0, 0);
}