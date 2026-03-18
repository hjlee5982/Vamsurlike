#include "pch.h"
#include "RenderManager.h"
#include "GameObject.h"
#include "ConstantBufferDesc.h"
#include "Material.h"
#include "Mesh.h"
#include "Camera.h"
#include "BoxCollider2D.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "UIText.h"
#include "Renderer.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "UIComponent.h"
#include "TMesh.h"
#include "RenderPass.h"

void RenderManager::Awake()
{
	// 상수 버퍼 생성
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	{
		desc.Usage          = D3D11_USAGE_DEFAULT;
		desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = 0;
	}
	{
		desc.ByteWidth = sizeof(CB_PerFrame);
		DEVICE->CreateBuffer(&desc, nullptr, &_cbPerFrame);
	}
	{
		desc.ByteWidth = sizeof(CB_PerObject);
		DEVICE->CreateBuffer(&desc, nullptr, &_cbPerObject);
	}

	// 와이어 프레임 레스터라이저 생성
	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&desc, sizeof(desc));
	{
		rsDesc.FillMode      = D3D11_FILL_WIREFRAME;
		rsDesc.CullMode      = D3D11_CULL_NONE;
		rsDesc.ScissorEnable = false;
	}
	DEVICE->CreateRasterizerState(&rsDesc, _wireFrameRS.GetAddressOf());

	// 기본 레스터라이저 생성
	ZeroMemory(&desc, sizeof(desc));
	{
		rsDesc.FillMode      = D3D11_FILL_SOLID;
		rsDesc.CullMode      = D3D11_CULL_NONE;
		rsDesc.ScissorEnable = false;
	}
	DEVICE->CreateRasterizerState(&rsDesc, _defaultRS.GetAddressOf());

	// DS스테이트 생성
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	{
		dsDesc.DepthEnable    = false;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.DepthFunc      = D3D11_COMPARISON_ALWAYS;
	}
	DEVICE->CreateDepthStencilState(&dsDesc, _dss.GetAddressOf());

	// 블랜드 스테이트 생성
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	{
		blendDesc.RenderTarget[0].BlendEnable			= TRUE;
		blendDesc.RenderTarget[0].SrcBlend				= D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend				= D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp				= D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha		= D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha			= D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}
	DEVICE->CreateBlendState(&blendDesc, _bs.GetAddressOf());

	// 샘플러 스테이트 생성
	D3D11_SAMPLER_DESC samplerDesc = {};
	{
		samplerDesc.Filter		   = D3D11_FILTER_MIN_MAG_MIP_POINT;
		samplerDesc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD         = 0;
		samplerDesc.MaxLOD         = D3D11_FLOAT32_MAX;
	}
	CHECK(DEVICE->CreateSamplerState(&samplerDesc, _ss.GetAddressOf()));

	// 포인트 샘플링
	CONTEXT->PSSetSamplers(0, 1, _ss.GetAddressOf());

	// 2D게임은 깊이테스트를 꺼야 추가 한 순서대로 그려짐
	CONTEXT->OMSetDepthStencilState(_dss.Get(), 0);

	// 2D는 블랜드를 켜줘야 함
	CONTEXT->OMSetBlendState(_bs.Get(), nullptr, 0xffffffff);


	// 렌더 패스 생성
	_spritePass        = makeSptr<SpriteRenderPass>();
	_tilemapPass	   = makeSptr<TilemapRenderPass>();
	_debugColliderPass = makeSptr<DebugColliderRenderPass>();
	_uiPass            = makeSptr<UIRenderPass>();
	_debugUIPass       = makeSptr<DebugUIRenderPass>();

	// 렌더 컨텍스트 생성
	_ctx.resize(3);
}

void RenderManager::CollectRenderData()
{
	// 오브젝트 렌더링 데이터 수집
	auto& ctx = _ctx[_write];
	ctx.Clear();
	
	for (auto& wRenderer : _renderers)
	{
		if (auto renderer = wRenderer.lock())
		{
			if (renderer->Owner()->isActive == true)
			{
				renderer->CollectRenderData(ctx);
			}
		}
	}

	// 콜라이더 렌더링 데이터 수집
	for (auto& wCollider : _colliders)
	{
		if (auto collider = wCollider.lock())
		{
			if (collider->Owner()->isActive == true)
			{
				collider->CollectRenderData(ctx);
			}
		}
	}

	// UI 렌더링 데이터 수집 (디버깅 데이터까지 같이 수집중)
	for (auto& wUI : _uis)
	{
		if (auto ui = wUI.lock())
		{
			if (ui->Owner()->isActive == true)
			{
				ui->CollectRenderData(ctx);
			}
		}
	}
}

void RenderManager::RenderGameObject()
{
	// 게임오브젝트 렌더링
	{
		// 게임오브젝트 상수버퍼 바인딩
		CB_PerFrame perFrameData;
		{
			perFrameData.viewMatrix = Global::ViewMatrix;
			perFrameData.projMatrix = Global::ProjMatrix;
		}
		CONTEXT->UpdateSubresource(_cbPerFrame.Get(), 0, nullptr, &perFrameData, 0, 0);
		CONTEXT->VSSetConstantBuffers(0, 1, _cbPerFrame.GetAddressOf());

		RenderSprite();
		RenderTilemap();

		if (colliderRendering == true)
		{
			RenderCollider();
		}
	}
	// UI 오브젝트 렌더링
	{
		// UI 오브젝트 상수버퍼 바인딩
		CB_PerFrame perFrameData;
		{
			perFrameData.viewMatrix = Global::UIViewMatrix;
			perFrameData.projMatrix = Global::UIProjMatrix;
		}
		CONTEXT->UpdateSubresource(_cbPerFrame.Get(), 0, nullptr, &perFrameData, 0, 0);
		CONTEXT->VSSetConstantBuffers(0, 1, _cbPerFrame.GetAddressOf());
		RenderUI();

		if (debugUIRendering == true)
		{
			RenderDebugUI();
		}
	}
}

void RenderManager::RenderSprite()
{
	// 스프라이트 렌더 데이터 바인딩
	_spritePass->Bind(_ctx[_read]);
}

void RenderManager::RenderTilemap()
{
	_tilemapPass->Bind(_ctx[_read]);
}

void RenderManager::RenderCollider()
{
	// 콜라이더는 와이어 프레임
	// 콜라이더는 일반 물체와 그리는 법이 달라서 토폴로지를 따로 설정해줘야 함
	CONTEXT->RSSetState(_wireFrameRS.Get());
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);


	// 콜라이더 렌더 데이터 바인딩
	_debugColliderPass->Bind(_ctx[_read]);


	// 와이어 프레임 해제
	// 토폴로지 원상복구
	CONTEXT->RSSetState(_defaultRS.Get());
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void RenderManager::RenderUI()
{
	// UI 렌더 데이터 바인딩
	_uiPass->Bind(_ctx[_read]);
}

void RenderManager::RenderDebugUI()
{
	// UI 경계는 와이어 프레임
	// UI 경계는 일반 물체와 그리는 법이 달라서 토폴로지를 따로 설정해줘야 함
	CONTEXT->RSSetState(_wireFrameRS.Get());
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);


	// UI 경계 렌더 데이터 바인딩
	_debugUIPass->Bind(_ctx[_read]);


	// 와이어 프레임 해제
	// 토폴로지 원상복구
	CONTEXT->RSSetState(_defaultRS.Get());
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void RenderManager::AddRenderer(sptr<Renderer> renderer)
{
	_renderers.push_back(renderer);
}

void RenderManager::AddCollider(sptr<Collider> collider)
{
	_colliders.push_back(collider);
}

void RenderManager::AddUI(sptr<UIComponent> ui)
{
	_uis.push_back(ui);
}

void RenderManager::SwapTripleContext()
{
	i32 next_read  = _write;
	i32 next_write = _free;
	i32 next_free  = _read;

	_write = _free;
	_read  = _write;
	_free  = _read;
}
