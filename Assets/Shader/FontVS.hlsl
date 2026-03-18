#include "CBuffer.hlsli"
#include "struct.hlsli"

PS_IN_UI main(VS_IN_UI input)
{
    PS_IN_UI output = (PS_IN_UI) 0;
    
    float4 position = float4(input.position, 1.f);
    
    position = mul(position, WorldMatrix);
    position = mul(position, ViewMatrix);
    position = mul(position, ProjMatrix);
    
    output.position = position;
    output.uv       = input.uv;
    output.color    = input.color;

    return output;
}