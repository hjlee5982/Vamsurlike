#include "pch.h"
#include "Texture.h"

void Texture::CreateTexture(const wstring& path)
{
    TexMetadata md;
    ScratchImage image;

    wchar_t szExt[20] = {};

    _wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 20);

    if (!wcscmp(szExt, L".dds") || !wcscmp(szExt, L".DDS"))
    {
        CHECK(::LoadFromDDSFile(path.c_str(), DDS_FLAGS_NONE, &md, image));
    }
    else
    {
        CHECK(::LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, &md, image));
    }

	CHECK(::CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), md, _srv.GetAddressOf()));

    _textureSize.x = md.width;
    _textureSize.y = md.height;
}

ComPtr<ID3D11ShaderResourceView> Texture::GetSRV()
{
    return _srv;
}
