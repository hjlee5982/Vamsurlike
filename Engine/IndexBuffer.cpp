#include "pch.h"
#include "IndexBuffer.h"

ComPtr<ID3D11Buffer> IndexBuffer::GetIndexBuffer()
{
	return _indexBuffer;
}

u32 IndexBuffer::GetStride()
{
	return _stride;
}

u32 IndexBuffer::GetIndexCount()
{
	return _indexCount;
}

u32 IndexBuffer::GetOffset()
{
	return _offset;
}
