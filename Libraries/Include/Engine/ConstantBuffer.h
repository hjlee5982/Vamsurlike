#pragma once

enum class EConstantBufferType
{
	Transform,
	Light,
	Global,
	Material,

	End
};

template<typename T>
class ConstantBuffer
{
public:
	ComPtr<ID3D11Buffer> GetConstantBuffer()
	{
		return _constantBuffer;
	}
public:
	void Create()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		{
			desc.ByteWidth      = sizeof(T);
			desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
			desc.Usage          = D3D11_USAGE_DYNAMIC;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}

		CHECK(DEVICE->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf()));
	}
	void CopyData(const T& data)
	{
		D3D11_MAPPED_SUBRESOURCE subResource;
		ZeroMemory(&subResource, sizeof(subResource));

		CONTEXT->Map(_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		::memcpy(subResource.pData, &data, sizeof(data));
		CONTEXT->Unmap(_constantBuffer.Get(), 0);
	}
private:
	ComPtr<ID3D11Buffer> _constantBuffer;
};

