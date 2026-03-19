#pragma once

#include "Geometry.h"
#include "VertexData.h"

class GeometryHelper
{
public:
	static void CreateSquare(sptr<Geometry<VertexColliderData>> geometry);
	static void CreateSquare(sptr<Geometry<VertexTextureData>>  geometry);
	static void CreateSquare(sptr<Geometry<VertexUIData>>       geometry);
public:
	static void CreateCircle(sptr<Geometry<VertexColliderData>> geometry);
	static void CreateCircle(sptr<Geometry<VertexTextureData>>  geometry);
	static void CreateCircle(sptr<Geometry<VertexUIData>>       geometry);
public:
	static void CreateCube(sptr<Geometry<VertexColliderData>> geometry);
	static void CreateCube(sptr<Geometry<VertexTextureData>>  geometry);
	static void CreateCube(sptr<Geometry<VertexUIData>>       geometry);
public:
	static void CreateSphere(sptr<Geometry<VertexColliderData>> geometry);
	static void CreateSphere(sptr<Geometry<VertexTextureData>>  geometry);
	static void CreateSphere(sptr<Geometry<VertexUIData>>       geometry);
public:
	static void CreateGrid(sptr<Geometry<VertexColliderData>> geometry, int size = 101);
	static void CreateGrid(sptr<Geometry<VertexTextureData>>  geometry, int size = 101);
	static void CreateGrid(sptr<Geometry<VertexUIData>>       geometry, int size = 101);
};