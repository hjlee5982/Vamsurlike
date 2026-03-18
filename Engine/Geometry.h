#pragma once

template<typename T>
class Geometry
{
public:
	u32 GetVertexCount()
	{
		return _vertices.size();
	}
	void* GetVertexData()
	{
		return _vertices.data();
	}
	const List<T>& GetVertices()
	{
		return _vertices;
	}
public:
	void SetVertices(const List<T>& vertices)
	{
		_vertices = vertices;
	}
public:
	u32 GetIndexCount()
	{
		return _indices.size();
	}
	void* GetIndexData()
	{
		return _indices.data();
	}
	const List<u32>& GetIndices()
	{
		return _indices;
	}
public:
	void SetIndices(const List<u32>& indices)
	{
		_indices = indices;
	}
private:
	List<T>   _vertices;
	List<u32> _indices;
};

