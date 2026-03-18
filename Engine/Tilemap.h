#pragma once

#include "Component.h"
#include "VertexData.h"

class Tilemap : public Component
{
	struct Tile
	{
		f32 u0;		f32 v0;
		f32 u1;		f32 v1;
	};
public:
	void SetTileSprite(const wstring& tag, int sliceSize);
	void SetTile(i32 tx, i32 ty, i32 x, i32 y);
public:
	sptr<class Texture> _texture;
	List<List<Tile>>    _tiles;
public:
	List<VertexTextureData> vtx;
	List<u32>				idx;
private:
	i32 base = 0;
};

