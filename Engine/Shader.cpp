#include "pch.h"
#include "Shader.h"

void Shader::CreateShader(const wstring& path)
{
	ComPtr<ID3DBlob> errorBlob;
	UINT compileFlags;

#if defined(DEBUG) || defined(_DEBUG)
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	string entry = "main";

	// VS 持失
	wstring vsPath = path + L"VS.hlsl";

	CHECK(D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "vs_5_0", compileFlags, 0, _vsByteCode.GetAddressOf(), errorBlob.GetAddressOf()));
	CHECK(DEVICE->CreateVertexShader(_vsByteCode->GetBufferPointer(), _vsByteCode->GetBufferSize(), nullptr, _vs.GetAddressOf()));
	
	// PS 持失
	wstring psPath = path + L"PS.hlsl";

	CHECK(D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), "ps_5_0", compileFlags, 0, _psByteCode.GetAddressOf(), errorBlob.GetAddressOf()));
	CHECK(DEVICE->CreatePixelShader(_psByteCode->GetBufferPointer(), _psByteCode->GetBufferSize(), nullptr, _ps.GetAddressOf()));
}

void Shader::Bind()
{
	CONTEXT->VSSetShader(_vs.Get(), nullptr, 0);
	CONTEXT->PSSetShader(_ps.Get(), nullptr, 0);
}