#include "pch.h"
#include "UIText.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "RenderManager.h"
#include "Material.h"
#include "AssetManager.h"
#include "VertexData.h"
#include "FontManager.h"
#include "Geometry.h"
#include "Mesh.h"
#include "TMesh.h"
#include "Transform.h"
#include "RenderCommand.h"

void UIText::Init()
{
	_mesh     = makeSptr<TMesh<VertexUIData>>();
	_geometry = makeSptr<Geometry<VertexUIData>>();
	_material = ASSET.Get<Material>(L"Material_UI_Font");

	RENDERER.AddUI(shared_from_this());
}

void UIText::CollectRenderData(RenderContext& ctx)
{
    UIRenderCommand cmd;
    {
        cmd.WorldMatrix = Owner()->transform->GetWorldMatrix();
        cmd.Color       = color;
        cmd.Mesh        = _mesh;
        cmd.Material    = _material;
    }
    ctx.uiCmds.push_back(cmd);

    DebugUIRenderCommand dbgCmd;
    {
        dbgCmd.WorldMatrix = Owner()->transform->GetWorldMatrix();
        dbgCmd.Color       = _debugColor;
        dbgCmd.Mesh        = _debugMesh;
        dbgCmd.Material    = _debugMaterial;
    }
    ctx.debugUICmds.push_back(dbgCmd);
}

void UIText::Text(const wstring& text)
{
    _text = text;

    struct Placement
    {
        f32 x0, y0, x1, y1;
    };
    List<Placement> placements;
    placements.reserve(_text.size());

    f32 cursorX    = 0.f;
    f32 baseLine   = 0.f;
    f32 totalWidth = 0.f;
    f32 maxHeight  = 0.f;


    ///////////////////////////////////////
    // 1 : 폰트 크기 측정
    ///////////////////////////////////////
    wchar_t prevChar = 0;

    f32 xObjScale = Owner()->transform->GetScale().x;
    f32 yObjScale = Owner()->transform->GetScale().y;

    for (i32 i = 0; i < text.size(); i++)
    {
        wchar_t ch = text[i];

        auto iter = FONT.glyphs.find((i32)ch);

        if (iter == FONT.glyphs.end())
        {
            continue;
        }

        const Glyph& g = iter->second;

        // kerning
        f32 kerning = 0.f;
        if (prevChar != 0)
        {
			kerning = FONT.GetKerning(prevChar, ch);
        }

        f32 advance      = g.xAdvance * _scale;
        f32 space        = _space * _scale;
        f32 totalAdvance = kerning * _scale + advance + space;


        f32 x0 = cursorX  + g.xOffset * _scale;
        f32 y0 = baseLine - g.yOffset * _scale;
        f32 x1 = x0 + g.witdh  * _scale;
        f32 y1 = y0 - g.height * _scale;

        placements.push_back({ x0, y0, x1, y1 });

        cursorX    += totalAdvance;
        totalWidth += totalAdvance;

        maxHeight = max(maxHeight, (f32)g.height * _scale);

        prevChar = ch;
    }


    ///////////////////////////////////////
    // 2 : 정렬, 피봇 계산
    ///////////////////////////////////////

    f32 pivotX = 0.f;
    f32 pivotY = 0.f;
    f32 VerticalPadding = 10.f;

    switch (_horizontal)
    {
	case EHorizontalAlignment::Left:   pivotX = 0.f;                break;
	case EHorizontalAlignment::Center: pivotX = -totalWidth * 0.5f; break;
	case EHorizontalAlignment::Right:  pivotX = -totalWidth;        break;
    }

    switch (_vertical)
    {
    case EVerticalAlignment::Top:    pivotY = yObjScale * 0.5f - VerticalPadding;              break;
    case EVerticalAlignment::Center: pivotY = maxHeight * 0.5f;                                break;
    case EVerticalAlignment::Bottom: pivotY = -yObjScale * 0.5f + maxHeight + VerticalPadding; break;
    }


    ///////////////////////////////////////
    // 3 : 정점 생성
    ///////////////////////////////////////
    List<VertexUIData> vtx;
    List<u32> idx;

    vtx.reserve(text.size() * 4);
    idx.reserve(text.size() * 6);

    for (i32 i = 0; i < text.size(); ++i)
    {
        wchar_t ch = text[i];

        auto iter = FONT.glyphs.find((i32)ch);

        if (iter == FONT.glyphs.end())
        {
            continue;
        }

        const Glyph& g = iter->second;

        f32 x0 = (placements[i].x0 + pivotX) / xObjScale;
        f32 y0 = (placements[i].y0 + pivotY) / yObjScale;
        f32 x1 = (placements[i].x1 + pivotX) / xObjScale;
        f32 y1 = (placements[i].y1 + pivotY) / yObjScale;

        // Vertices
        vtx.push_back({ Vector3(x0,y0, 0.f), Vector2(g.u0, g.v0), _color });
        vtx.push_back({ Vector3(x1,y0, 0.f), Vector2(g.u1, g.v0), _color });
        vtx.push_back({ Vector3(x1,y1, 0.f), Vector2(g.u1, g.v1), _color });
        vtx.push_back({ Vector3(x0,y1, 0.f), Vector2(g.u0, g.v1), _color });

        // Indices
        i32 base = i * 4;
		idx.push_back(base + 0); idx.push_back(base + 1); idx.push_back(base + 2);
		idx.push_back(base + 0); idx.push_back(base + 2); idx.push_back(base + 3);
    }

    _geometry->SetVertices(vtx);
    _geometry->SetIndices(idx);

    _mesh->CreateMesh(_geometry);
}

void UIText::Alignment(EHorizontalAlignment horizontal, EVerticalAlignment vertical)
{
	_vertical = vertical; _horizontal = horizontal; Text(_text);
}

void UIText::Scale(i32 scale)
{
	_scale = (f32)scale / (f32)FONT._lineHeight; Text(_text);
}

void UIText::Space(i32 space)
{
    _space = space; Text(_text);
}

void UIText::Color(Vector4 color)
{
    _color = color; Text(_text);
}
