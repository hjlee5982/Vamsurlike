#pragma once

#include "Renderer.h"

class SpriteRenderer : public Renderer, public std::enable_shared_from_this<SpriteRenderer>
{
public:
	virtual void Init() override;
public:
	virtual void CollectRenderData(RenderContext& ctx) override;
public:
	i32 OrderInLayer = 0;
};