#include "pch.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateSquare(sptr<Geometry<VertexColliderData>> geometry)
{
	f32 padding = 0.0f;

	List<VertexColliderData> vtx;
	{
		vtx.push_back({ Vector3(-0.5f - padding,  0.5f + padding, 0.f) });
		vtx.push_back({ Vector3( 0.5f + padding,  0.5f + padding, 0.f) });
		vtx.push_back({ Vector3( 0.5f + padding, -0.5f - padding, 0.f) });
		vtx.push_back({ Vector3(-0.5f - padding, -0.5f - padding, 0.f) });

		geometry->SetVertices(vtx);
	}

	List<u32> idx = { 0, 1, 1, 2, 2, 3, 3, 0 };
	{
		geometry->SetIndices(idx);
	}
}

void GeometryHelper::CreateSquare(sptr<Geometry<VertexTextureData>> geometry)
{
	List<VertexTextureData> vtx;
	{
		vtx.push_back({ Vector3(-0.5f,  0.5f, 0.f), Vector2(0.f, 0.f) });
		vtx.push_back({ Vector3( 0.5f,  0.5f, 0.f), Vector2(1.f, 0.f) });
		vtx.push_back({ Vector3( 0.5f, -0.5f, 0.f), Vector2(1.f, 1.f) });
		vtx.push_back({ Vector3(-0.5f, -0.5f, 0.f), Vector2(0.f, 1.f) });

		geometry->SetVertices(vtx);
	}

	List<u32> idx = { 0, 1, 2, 0, 2, 3 };
	{
		geometry->SetIndices(idx);
	}
}

void GeometryHelper::CreateSquare(sptr<Geometry<VertexUIData>> geometry)
{
	List<VertexUIData> vtx;
	{
		vtx.push_back({ Vector3(-0.5f,  0.5f, 0.f), Vector2(0.f, 0.f), Vector4(1.f, 1.f, 1.f, 1.f) });
		vtx.push_back({ Vector3( 0.5f,  0.5f, 0.f), Vector2(1.f, 0.f), Vector4(1.f, 1.f, 1.f, 1.f) });
		vtx.push_back({ Vector3( 0.5f, -0.5f, 0.f), Vector2(1.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f) });
		vtx.push_back({ Vector3(-0.5f, -0.5f, 0.f), Vector2(0.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f) });

		geometry->SetVertices(vtx);
	}

	List<u32> idx = { 0, 1, 2, 0, 2, 3 };
	{
		geometry->SetIndices(idx);
	}
}





void GeometryHelper::CreateCircle(sptr<Geometry<VertexColliderData>> geometry)
{
	List<VertexColliderData> vtx;
	List<u32> idx;
	
	vtx.push_back({ Vector3(0, 0, 0) });
	idx.push_back(0);

	f32 radius = 0.49f;

	i32 segment = 60;

	f32 eachAngle = XM_2PI / segment;

	for (i32 i = 0; i <= segment; ++i)
	{
		f32 angle = i * eachAngle;
		f32 x = radius * cosf(angle);
		f32 y = radius * sinf(angle);

		vtx.push_back({ Vector3(x, y, 0.f) });
		idx.push_back(i + 1);
		idx.push_back(i + 1);
	}

	geometry->SetVertices(vtx);
	geometry->SetIndices(idx);
}

void GeometryHelper::CreateCircle(sptr<Geometry<VertexTextureData>> geometry)
{
}

void GeometryHelper::CreateCircle(sptr<Geometry<VertexUIData>> geometry)
{
}





void GeometryHelper::CreateCube(sptr<Geometry<VertexColliderData>> geometry)
{
}

void GeometryHelper::CreateCube(sptr<Geometry<VertexTextureData>> geometry)
{
}

void GeometryHelper::CreateCube(sptr<Geometry<VertexUIData>> geometry)
{
}





void GeometryHelper::CreateSphere(sptr<Geometry<VertexColliderData>> geometry)
{
}

void GeometryHelper::CreateSphere(sptr<Geometry<VertexTextureData>> geometry)
{

}

void GeometryHelper::CreateSphere(sptr<Geometry<VertexUIData>> geometry)
{
}





void GeometryHelper::CreateGrid(sptr<Geometry<VertexColliderData>> geometry, int size)
{
}
void GeometryHelper::CreateGrid(sptr<Geometry<VertexTextureData>> geometry, int size)
{
	List<VertexTextureData> vtx;

	f32 d = (size / 2.f) - 0.5f;

	for (i32 i = 0; i < size; ++i)
	{
		for (i32 j = 0; j < size; ++j)
		{
			VertexTextureData v;
			{
				v.position = Vector3(j - d, i - d, 0);
				v.uv	   = Vector2((f32)j / (size - 1), (f32)i / (size - 1));
			}
			vtx.push_back(v);
		}
	}
	geometry->SetVertices(vtx);

	List<u32> idx;

	for (i32 i = 0; i < size - 1; ++i)
	{
		for (i32 j = 0; j < size - 1; ++j)
		{
			u32 index = i * size + j;

			idx.push_back(index);
			idx.push_back(index + size);
			idx.push_back(index + 1);

			idx.push_back(index + 1);
			idx.push_back(index + size);
			idx.push_back(index + size + 1);
		}
	}
	geometry->SetIndices(idx);
}

void GeometryHelper::CreateGrid(sptr<Geometry<VertexUIData>> geometry, int size)
{
}