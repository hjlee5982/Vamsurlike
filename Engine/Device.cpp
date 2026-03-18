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
		desc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
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