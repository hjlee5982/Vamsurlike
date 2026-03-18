#pragma once

struct VertexColliderData
{
	Vector3 position = { 0.f, 0.f, 0.f };

	static List<D3D11_INPUT_ELEMENT_DESC> GetInputLayoutDesc()
	{
		return
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
	}
};

struct VertexTextureData
{
	Vector3 position = { 0.f, 0.f, 0.f };
	Vector2 uv       = { 0.f, 0.f      };

	static List<D3D11_INPUT_ELEMENT_DESC> GetInputLayoutDesc()
	{
		return
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
	}
};

struct VertexUIData
{
	Vector3 position = { 0.f, 0.f, 0.f      };
	Vector2 uv       = { 0.f, 0.f           };
	Vector4 color    = { 0.f, 0.f, 0.f, 0.f };

	static List<D3D11_INPUT_ELEMENT_DESC> GetInputLayoutDesc()
	{
		return
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,   0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,      0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
	}
};