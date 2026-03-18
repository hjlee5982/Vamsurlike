#pragma once

class IndexBuffer
{
public:
	ComPtr<ID3D11Buffer> GetIndexBuffer();
public:
	u32 GetStride();
	u32 GetIndexCount();
	u32 GetOffset();
public:
	void Create(const List<u32>& indices)
	{
		_stride     = sizeof(u32);
		_indexCount = indices.size();

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		{
			desc.ByteWidth = _stride * _indexCount;
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			desc.Usage     = D3D11_USAGE_IMMUTABLE;
		}

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		{
			data.pSysMem = indices.data();
		}

		CHECK(DEVICE->CreateBuffer(&desc, &data, _indexBuffer.GetAddressOf()));
	}
	void PushData()
	{
		CONTEXT->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}
private:
	ComPtr<ID3D11Buffer> _indexBuffer;
private:
	u32 _stride     = 0;
	u32 _offset     = 0;
	u32 _indexCount = 0;
};

