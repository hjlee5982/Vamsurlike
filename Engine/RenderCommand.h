#pragma once

struct SpriteRenderCommand
{
	Matrix				  WorldMatrix;
	sptr<class TMeshBase> Mesh;
	sptr<class Material>  Material;
	i32					  OrderInLayer;
};

struct TilemapRenderCommand
{
	Matrix				  WorldMatrix;
	sptr<class TMeshBase> Mesh;
	sptr<class Material>  Material;
	i32				      OrderInLayer;
};

struct DebugColliderRenderCommand
{
	Matrix				  WorldMatrix;
	Vector4				  Color;
	sptr<class TMeshBase> Mesh;
	sptr<class Material>  Material;
};

struct UIRenderCommand
{
	Matrix				  WorldMatrix;
	Vector4				  Color;
	sptr<class TMeshBase> Mesh;
	sptr<class Material>  Material;
};

struct DebugUIRenderCommand
{
	Matrix				  WorldMatrix;
	Vector4				  Color;
	sptr<class TMeshBase> Mesh;
	sptr<class Material>  Material;
};

struct RenderContext
{
	List<SpriteRenderCommand>        spriteCmds;
	List<TilemapRenderCommand>		 tilemapCmds;
	List<DebugColliderRenderCommand> debugColliderCmds;
	List<UIRenderCommand>            uiCmds;
	List<DebugUIRenderCommand>       debugUICmds;

	void Clear()
	{
		spriteCmds		 .clear();
		debugColliderCmds.clear();
		uiCmds			 .clear();
		debugUICmds		 .clear();
	}
};