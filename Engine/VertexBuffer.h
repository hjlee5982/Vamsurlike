#pragma once

class VertexBuffer
{
public:
	ComPtr<ID3D11Buffer> GetVertexBuffer();
public:
	u32 GetStride();
	u32 GetvertexCount();
	u32 GetOffset();
	u32 GetSlot();
public:
	template<typename T>
	void Create(const List<T>& vertices, u32 slot = 0, bool cpuWrite = false, bool gpuWrite = false)
	{
		_stride      = sizeof(T);
		_vertexCount = vertices.size();

		_slot     = slot;
		_cpuWrite = cpuWrite;
		_gpuWrite = gpuWrite;

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		{
			desc.ByteWidth = _stride * _vertexCount;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.Usage     = D3D11_USAGE_IMMUTABLE;
		}

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		{
			data.pSysMem = vertices.data();
		}

		CHECK(DEVICE->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf()));
	}
	void PushData()
	{
		CONTEXT->IASetVertexBuffers(_slot, 1, _vertexBuffer.GetAddressOf(), &_stride, &_offset);
	}
private:
	ComPtr<ID3D11Buffer> _vertexBuffer;
private:
	u32 _stride      = 0;
	u32 _vertexCount = 0;
	u32 _offset      = 0;
	u32 _slot        = 0;
private:
	bool _cpuWrite;
	bool _gpuWrite;
};

