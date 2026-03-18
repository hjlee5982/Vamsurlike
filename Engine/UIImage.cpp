#include "pch.h"
#include "UIImage.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Material.h"
#include "TMesh.h"
#include "RenderManager.h"
#include "RenderCommand.h"

void UIImage::Init()
{
	_mesh     = ASSET.Get<TMesh<VertexUIData>>(L"Mesh_UI_Square");
	_material = ASSET.Get<Material>(L"Material_UI_Image");

	RENDERER.AddUI(shared_from_this());
}

void UIImage::CollectRenderData(RenderContext& ctx)
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
		dbgCmd.Color	   = _debugColor;
		dbgCmd.Mesh        = _debugMesh;
		dbgCmd.Material    = _debugMaterial;
	}
	ctx.debugUICmds.push_back(dbgCmd);
}
