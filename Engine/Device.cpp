#include "pch.h"
#include "Device.h"

void Device::Awake()
{
	_option = Global::ClientOption;

	CreateDeviceAndSwapChain();
	CreateBackBufferRTV();
	CreateDSV();
	SetViewport();
}

void Device::RenderBegin()
{
	_context->OMSetRenderTargets   (1, _backBufferRTV.GetAddressOf(), _DSV.Get());
	_context->ClearRenderTargetView(_backBufferRTV.Get(), (float*)(&_option.clearColor));
	_context->ClearDepthStencilView(_DSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	_context->RSSetViewports       (1, &_viewport);
}

void Device::RenderEnd()
{
	CHECK(_swapChain->Present(1, 0));
}

void Device::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	{
		desc.BufferDesc.Width                   = _option.width;
		desc.BufferDesc.Height                  = _option.height;
		desc.BufferDesc.RefreshRate.Numerator   = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count                   = 1;
		desc.SampleDesc.Quality                 = 0;
		desc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount                        = 1;
		desc.OutputWindow                       = _option.hWnd;
		desc.Windowed							= TRUE;
		desc.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;
	}

	CHECK(::D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		_swapChain.GetAddressOf(),
		_device.GetAddressOf(),
		nullptr,
		_context.GetAddressOf()
	));
}

void Device::CreateBackBufferRTV()
{
	CHECK(_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)_backBufferTexture.GetAddressOf()));

	CHECK(_device->CreateRenderTargetView(_backBufferTexture.Get(), nullptr, _backBufferRTV.GetAddressOf()));
}

void Device::CreateDSV()
{
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	{
		textureDesc.Width              = static_cast<u32>(_option.width);
		textureDesc.Height             = static_cast<u32>(_option.height);
		textureDesc.MipLevels          = 1;
		textureDesc.ArraySize          = 1;
		textureDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
		textureDesc.SampleDesc.Count   = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage              = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
		textureDesc.CPUAccessFlags     = 0;
		textureDesc.MiscFlags          = 0;
	}
	CHECK(DEVICE->CreateTexture2D(&textureDesc, nullptr, _DSTexture.GetAddressOf()));


	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	{
		dsvDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvDesc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;
	}
	CHECK(DEVICE->CreateDepthStencilView(_DSTexture.Get(), &dsvDesc, _DSV.GetAddressOf()));
}

void Device::SetViewport()
{
	_viewport.TopLeftX = 0;
	_viewport.TopLeftY = 0;
	_viewport.Width    = _option.width;
	_viewport.Height   = _option.height;
	_viewport.MinDepth = 0;
	_viewport.MaxDepth = 1;
}



// 에디터에 쓸 SRV 만들기
//void Device::CreateEditorSRV()
//{
//	D3D11_TEXTURE2D_DESC texDesc;
//	ZeroMemory(&texDesc, sizeof(texDesc));
//	{
//		texDesc.Width            = _option.width;
//		texDesc.Height           = _option.height;
//		texDesc.MipLevels        = 1;
//		texDesc.ArraySize        = 1;
//		texDesc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
//		texDesc.SampleDesc.Count = 1;
//		texDesc.Usage            = D3D11_USAGE_DEFAULT;
//		texDesc.BindFlags        = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
//	}
//	CHECK(DEVICE->CreateTexture2D(&texDesc, nullptr, _editorTexture.GetAddressOf()));
//
//	CHECK(DEVICE->CreateRenderTargetView(_editorTexture.Get(), nullptr, _editorRTV.GetAddressOf()));
//
//	CHECK(DEVICE->CreateShaderResourceView(_editorTexture.Get(), nullptr, _editorSRV.GetAddressOf()));
//}

// 백버퍼에서 SRV 뽑아오기
// 
//void Device::CreateRenderTargetTexture()
//{
//	if (nullptr != _backBufferSRV)
//	{
//		_backBufferSRV->Release();
//	}
//
//	HRESULT hr;
//	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
//
//	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
//	CHECK(hr);
//
//	D3D11_TEXTURE2D_DESC backBufferDesc;
//	backBuffer->GetDesc(&backBufferDesc);
//	
//	D3D11_TEXTURE2D_DESC tempDesc = backBufferDesc;
//	{
//		tempDesc.Usage          = D3D11_USAGE_STAGING;
//		tempDesc.BindFlags      = 0;
//		tempDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
//		tempDesc.MiscFlags      = 0;
//	}
//	
//	ComPtr<ID3D11Texture2D> tempTexture = nullptr;
//	hr = DEVICE->CreateTexture2D(&tempDesc, nullptr, tempTexture.GetAddressOf());
//	CHECK(hr);
//
//	CONTEXT->CopyResource(tempTexture.Get(), backBuffer.Get());
//	
//	D3D11_MAPPED_SUBRESOURCE mappedResource;
//	hr = CONTEXT->Map(tempTexture.Get(), 0, D3D11_MAP_READ, 0, &mappedResource);
//	CHECK(hr);
//	
//	BYTE* pData = reinterpret_cast<BYTE*>(mappedResource.pData);
//	vector<BYTE> imageData(backBufferDesc.Width * backBufferDesc.Height * 4);
//	memcpy(imageData.data(), pData, imageData.size());
//	
//	CONTEXT->Unmap(tempTexture.Get(), 0);
//	
//	
//	D3D11_TEXTURE2D_DESC textureDesc;
//	ZeroMemory(&textureDesc, sizeof(textureDesc));
//	{
//		textureDesc.Width			 = backBufferDesc.Width;
//		textureDesc.Height			 = backBufferDesc.Height;
//		textureDesc.MipLevels		 = 1;
//		textureDesc.ArraySize		 = 1;
//		textureDesc.Format			 = backBufferDesc.Format;
//		textureDesc.SampleDesc.Count = 1;
//		textureDesc.Usage            = D3D11_USAGE_DEFAULT;
//		textureDesc.BindFlags        = D3D11_BIND_SHADER_RESOURCE;
//		textureDesc.CPUAccessFlags   = 0;
//	}
//	
//	D3D11_SUBRESOURCE_DATA initData;
//	ZeroMemory(&initData, sizeof(initData));
//	{
//		initData.pSysMem     = imageData.data();
//		initData.SysMemPitch = backBufferDesc.Width * 4;
//	}
//	
//	ComPtr<ID3D11Texture2D> pTexture = nullptr;
//	hr = DEVICE->CreateTexture2D(&textureDesc, &initData, pTexture.GetAddressOf());
//	CHECK(hr);
//
//	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
//	ZeroMemory(&desc, sizeof(desc));
//	{
//		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//		desc.Texture2D.MipLevels = 1;
//	}
//
//	hr = DEVICE->CreateShaderResourceView(pTexture.Get(), nullptr, _backBufferSRV.GetAddressOf());
//	CHECK(hr);
//
//	backBuffer->Release();
//}