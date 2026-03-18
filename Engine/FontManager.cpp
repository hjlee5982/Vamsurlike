#include "pch.h"
#include "FontManager.h"
#include "Texture.h"
#include "AssetManager.h"
#include "Mesh.h"

using namespace std;

void FontManager::Awake()
{
	string dir = "../Data/Font/EngineFont.fnt";

	Load(dir);
}

i32 FontManager::GetKerning(i32 first, i32 second)
{
	i64 key = ((i64)first << 32) | (i64)second;

	auto iter = kernings.find(key);

	if (iter != kernings.end())
	{
		return iter->second;
	}

	return 0;
}

bool FontManager::Load(const string& fileName)
{
	ifstream file(fileName);

	if (!file.is_open())
	{
		return false;
	}

	string line;

	while (getline(file, line))
	{
		stringstream ss(line);
		string word;
		ss >> word;

		if (word == "common")
		{
			ParseCommon(line);
		}
		else if (word == "page")
		{
			ParsePage(line);
		}
		else if (word == "char")
		{
			ParseChar(line);
		}
		else if (word == "Kerning")
		{

		}
	}

	return true;
}

void FontManager::ParseCommon(const string& line)
{
	auto dict = Tokenize(line);
	_textureWidth = stoi(dict["scaleW"]);
	_textureHeight = stoi(dict["scaleH"]);
	_lineHeight = stoi(dict["lineHeight"]);
}

void FontManager::ParsePage(const string& line)
{
	auto dict = Tokenize(line);
	_textureFile = dict["file"];
	_textureFile.erase(remove(_textureFile.begin(), _textureFile.end(), '"'), _textureFile.end());
}

void FontManager::ParseChar(const string& line)
{
	auto dict = Tokenize(line);

	Glyph g;
	{
		g.id       = stoi(dict["id"]);
		g.x        = stoi(dict["x"]);
		g.y        = stoi(dict["y"]);
		g.witdh    = stoi(dict["width"]);
		g.height   = stoi(dict["height"]);
		g.xOffset  = stoi(dict["xoffset"]);
		g.yOffset  = stoi(dict["yoffset"]);
		g.xAdvance = stoi(dict["xadvance"]);
	}
	{
		g.u0 = g.x / (f32)_textureWidth;
		g.v0 = g.y / (f32)_textureHeight;
		g.u1 = (g.x + g.witdh) / (f32)_textureWidth;
		g.v1 = (g.y + g.height) / (f32)_textureHeight;
	}
	glyphs[g.id] = g;
}

void FontManager::ParseKerning(const string& line)
{
	auto dict = Tokenize(line);

	i32 first = stoi(dict["first"]);
	i32 second = stoi(dict["second"]);
	i32 amount = stoi(dict["amount"]);

	i64 key = ((i64)first << 32 | (i64)second);

	kernings[key] = amount;
}

Dictionary<string, string> FontManager::Tokenize(const string& line)
{
	Dictionary<string, string> values;
	stringstream ss(line);
	string token;

	ss >> token;

	while (ss >> token)
	{
		auto equalPos = token.find('=');

		if (equalPos != string::npos)
		{
			string key = token.substr(0, equalPos);
			string value = token.substr(equalPos + 1);

			values[key] = value;
		}
	}

	return values;
}
