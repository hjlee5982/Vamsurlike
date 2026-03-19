#pragma once

class IRenderPass
{
public:
	IRenderPass();
public:
	virtual void Bind(struct RenderContext& ctx) = 0;
protected:
	ComPtr<ID3D11Buffer> _cbPerObject;
};


class SpriteRenderPass : public IRenderPass
{
public:
	virtual void Bind(struct RenderContext& ctx) override;
};



class TilemapRenderPass : public IRenderPass
{
public:
	virtual void Bind(struct RenderContext& ctx) override;
};


class DebugObjectRenderPass : public IRenderPass
{
public:
	virtual void Bind(struct RenderContext& ctx) override;
};


class DebugColliderRenderPass : public IRenderPass
{
public:
	virtual void Bind(struct RenderContext& ctx) override;
};



class UIRenderPass : public IRenderPass
{
public:
	virtual void Bind(struct RenderContext& ctx) override;
};



class DebugUIRenderPass : public IRenderPass
{
public:
	virtual void Bind(struct RenderContext& ctx) override;
};