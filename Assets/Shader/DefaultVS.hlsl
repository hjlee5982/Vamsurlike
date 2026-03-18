#include "CBuffer.hlsli"
#include "struct.hlsli"

PS_IN_TEXTURE main(VS_IN_TEXTURE input)
{
    PS_IN_TEXTURE output = (PS_IN_TEXTURE) 0;
    
    float4 position = float4(input.position, 1.f);
    
    position = mul(position, WorldMatrix);
    position = mul(position, ViewMatrix);
    position = mul(position, ProjMatrix);
    
    output.position = position;
    output.uv       = input.uv;
    
    return output;
}