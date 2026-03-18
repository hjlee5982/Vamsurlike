#pragma once

#include "Asset.h"

class Shader : public Asset
{
public:
	Shader() : Asset(EAssetType::Shader) {}
public:
	void CreateShader(const wstring& path);
	void Bind();
public:
	ComPtr<ID3DBlob> GetVSByteCode()
	{
		return _vsByteCode;
	}
private:
	ComPtr<ID3D11VertexShader> _vs;
	ComPtr<ID3D11PixelShader>  _ps;
private:
	ComPtr<ID3DBlob> _vsByteCode;
	ComPtr<ID3DBlob> _psByteCode;
	ComPtr<ID3D11InputLayout> _inputLayout;
};