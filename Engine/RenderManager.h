#pragma once


#include "RenderCommand.h"


class Renderer;
class Component;
class Collider;
class GameObject;
class UIComponent;
class SpriteRenderPass;
class TilemapRenderPass;
class DebugColliderRenderPass;
class UIRenderPass;
class DebugUIRenderPass;

class RenderManager : public Singleton<RenderManager>
{
public:
	virtual void Awake() override;
public:
	void CollectRenderData();
	void RenderGameObject();
private:
	void RenderSprite();
	void RenderTilemap();
	void RenderCollider();
	void RenderUI();
	void RenderDebugUI();
public:
	void AddRenderer(sptr<Renderer> renderer);
	void AddCollider(sptr<Collider> collider);
	void AddUI(sptr<UIComponent> ui);
public:
	bool colliderRendering = false;
	bool debugUIRendering  = false;
private:
	List<wptr<Renderer>>    _renderers;
	List<wptr<Collider>>    _colliders;
	List<wptr<UIComponent>> _uis;
private:
	sptr<SpriteRenderPass>        _spritePass;
	sptr<TilemapRenderPass>		  _tilemapPass;
	sptr<DebugColliderRenderPass> _debugColliderPass;
	sptr<UIRenderPass>            _uiPass;
	sptr<DebugUIRenderPass>       _debugUIPass;
private:
	ComPtr<ID3D11Buffer> _cbPerFrame;
	ComPtr<ID3D11Buffer> _cbPerObject;
private:
	ComPtr<ID3D11RasterizerState> _wireFrameRS;
	ComPtr<ID3D11RasterizerState> _defaultRS;
private:
	ComPtr<ID3D11DepthStencilState> _dss;
private:
	ComPtr<ID3D11BlendState>   _bs;
	ComPtr<ID3D11SamplerState> _ss;

	// 멀티스레딩
public:
	void SwapContext()
	{
		std::swap(_read, _write);
	}
	// 삼중 버퍼링
public:
	void SwapTripleContext();
private:
	List<RenderContext> _ctx;
	i32 _write = 0;
	i32 _read  = 1;
	i32 _free  = 2;
};