#pragma once

class Device : public Singleton<Device>
{
public:
	virtual void Awake() override;
public:
	void RenderBegin();
	void RenderEnd();
public:
	ComPtr<ID3D11Device>        GetDevice()  { return _device;  }
	ComPtr<ID3D11DeviceContext> GetContext() { return _context; }
public:
	ComPtr<ID3D11RenderTargetView>   GetBackBufferRTV()  { return _backBufferRTV; }
	ComPtr<ID3D11DepthStencilView>   GetDSV()            { return _DSV;           }
public:
	f32 GetWidth()  { return _viewport.Width;  }
	f32 GetHeight() { return _viewport.Height; }
private:
	void CreateDeviceAndSwapChain();
	void CreateBackBufferRTV();
	void CreateDSV();
private:
	void SetViewport();
private:
	ComPtr<ID3D11Device>		_device;
	ComPtr<ID3D11DeviceContext> _context;
	ComPtr<IDXGISwapChain>		_swapChain;
private:
	ComPtr<ID3D11Texture2D>        _backBufferTexture;
	ComPtr<ID3D11RenderTargetView> _backBufferRTV;
private:
	ComPtr<ID3D11Texture2D>         _DSTexture;
	ComPtr<ID3D11DepthStencilView>  _DSV;
private:
	ClientOption   _option;
	D3D11_VIEWPORT _viewport;	
};

