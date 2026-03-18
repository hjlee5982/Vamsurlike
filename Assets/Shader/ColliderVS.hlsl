#include "CBuffer.hlsli"
#include "struct.hlsli"

PS_IN_COLLIDER main(VS_IN_COLLIDER input)
{
    PS_IN_COLLIDER output = (PS_IN_COLLIDER) 0;
    
    float4 position = float4(input.position, 1.f);
    
    position = mul(position, WorldMatrix);
    position = mul(position, ViewMatrix);
    position = mul(position, ProjMatrix);
    
    output.position = position;

    return output;
}