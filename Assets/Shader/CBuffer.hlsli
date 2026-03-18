#ifndef __GLOBAL__
#define __GLOBAL__

cbuffer PerFrame : register(b0)
{
    row_major matrix ViewMatrix;
    row_major matrix ProjMatrix;
}

cbuffer PerObject : register(b1)
{
    row_major matrix WorldMatrix;
    float4 UIColor;
}

Texture2D gTexture_0 : register(t0);

SamplerState gLinearSampler : register(s0);
#endif