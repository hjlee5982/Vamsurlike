#pragma once

#include "UIComponent.h"

class UIImage : public UIComponent, public std::enable_shared_from_this<UIImage>
{
public:
	virtual void Init() override;
	virtual void CollectRenderData(struct RenderContext& ctx) override;
};

