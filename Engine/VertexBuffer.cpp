#include "pch.h"
#include "VertexBuffer.h"

ComPtr<ID3D11Buffer> VertexBuffer::GetVertexBuffer()
{
    return _vertexBuffer;
}

u32 VertexBuffer::GetStride()
{
    return _stride;
}

u32 VertexBuffer::GetvertexCount()
{
    return _vertexCount;
}

u32 VertexBuffer::GetOffset()
{
    return _offset;
}

u32 VertexBuffer::GetSlot()
{
    return _slot;
}
