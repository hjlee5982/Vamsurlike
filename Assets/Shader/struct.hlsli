#ifndef __STRUCT__
#define __STRUCT__

struct VS_IN_COLLIDER
{
    float3 position : POSITION;
};
struct PS_IN_COLLIDER
{
    float4 position : SV_Position;
};

struct VS_IN_TEXTURE
{
    float3 position : POSITION;
    float2 uv       : TEXCOORD0;
};
struct PS_IN_TEXTURE
{
    float4 position : SV_Position;
    float2 uv       : TEXCOORD0;
};

struct VS_IN_UI
{
    float3 position : POSITION;
    float2 uv       : TEXCOORD0;
    float4 color    : COLOR;
};
struct PS_IN_UI
{
    float4 position : SV_Position;
    float2 uv       : TEXCOORD0;
    float4 color    : COLOR0;
};


#endif