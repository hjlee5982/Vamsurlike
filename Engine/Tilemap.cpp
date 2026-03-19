#include "pch.h"
#include "Tilemap.h"
#include "AssetManager.h"
#include "Texture.h"

void Tilemap::SetTileSprite(const wstring& tag, int sliceSize)
{
	_texture = ASSET.Get<Texture>(tag);

	int textureX = _texture->_textureSize.x;
	int textureY = _texture->_textureSize.y;

	int tilePerX = textureX / sliceSize;
	int tilePerY = textureY / sliceSize;

	List<List<Tile>> tiles(tilePerY, List<Tile>(tilePerX));

	for (i32 i = 0; i < tilePerY; ++i)
	{
		for (i32 j = 0; j < tilePerX; ++j)
		{
			Tile tile;
			{
				tile.u0 = f32(j * sliceSize) / textureX;
				tile.v0 = 1.0f - f32(i * sliceSize) / textureY;
			}
			{
				tile.u1 = f32((j + 1) * sliceSize) / textureX;
				tile.v1 = 1.0f - f32((i + 1) * sliceSize) / textureY;
			}

			tiles[i][j] = tile;
		}
	}

	_tiles = tiles;
}

void Tilemap::SetTile(i32 tx, i32 ty, i32 x, i32 y)
{
	vtx.push_back({ Vector3(x     , y     , 0), Vector2(_tiles[ty][tx].u0 , _tiles[ty][tx].v0 ) });
	vtx.push_back({ Vector3(x + 1 , y     , 0), Vector2(_tiles[ty][tx].u1 , _tiles[ty][tx].v0 ) });
	vtx.push_back({ Vector3(x + 1 , y + 1 , 0), Vector2(_tiles[ty][tx].u1 , _tiles[ty][tx].v1 ) });
	vtx.push_back({ Vector3(x     , y + 1 , 0), Vector2(_tiles[ty][tx].u0 , _tiles[ty][tx].v1 ) });

	idx.push_back(base + 0);
	idx.push_back(base + 1);
	idx.push_back(base + 2);
	idx.push_back(base + 0);
	idx.push_back(base + 2);
	idx.push_back(base + 3);

	base += 4;
}

void Tilemap::SetTile(const wstring& path)
{
	std::ifstream file(path);
	List<string> lines;

	if (!file.is_open())
	{
		int a = 0;
	}

	string line;

	while (std::getline(file, line))
	{
		if (line.empty())
		{
			continue;
		}

		std::stringstream ss(line);
		string token;

		while (std::getline(ss, token, '\t'))
		{
			if (token.empty())
			{
				continue;
			}

			if (token.front() == '"')
			{
				token.erase(0, 1);
			}
			if (token.back() == '"')
			{
				token.pop_back();
			}

			std::stringstream ts(token);

			i32 tx, ty, x, y;
			char comma;

			ts >> tx >> comma >> ty >> comma >> x >> comma >> y;
			SetTile(tx, ty, x, y);
		}
	}
}
