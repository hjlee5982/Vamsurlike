#pragma once

#include "Geometry.h"
#include "TMesh.h"
#include "UIComponent.h"
#include "VertexData.h"

class Material;
class IndexBuffer;
class VertexBuffer;

enum class EHorizontalAlignment
{
	Left,
	Center,
	Right
};

enum class EVerticalAlignment
{
	Top,
	Center,
	Bottom,
};

class UIText : public UIComponent, public std::enable_shared_from_this<UIText>
{
public:
	virtual void Init() override;
	virtual void CollectRenderData(struct RenderContext& ctx) override;
public:
	void Text(const wstring& text);
	void Alignment(EHorizontalAlignment horizontal, EVerticalAlignment vertical = EVerticalAlignment::Center);
	void Scale(i32 scale);
	void Space(i32 space);
	void Color(Vector4 color);
public:
	sptr<Geometry<VertexUIData>> _geometry;
private:
	wstring _text = L"New Text";
private:
	EHorizontalAlignment _horizontal = EHorizontalAlignment::Left;
	EVerticalAlignment   _vertical   = EVerticalAlignment::Center;
private:
	f32     _scale = 1.f;
	f32     _space = 0.f;
	Vector4 _color = Vector4::One;
};

