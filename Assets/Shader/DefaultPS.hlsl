#include "CBuffer.hlsli"
#include "Struct.hlsli"

float4 main(PS_IN_TEXTURE input) : SV_TARGET
{
    float4 color = gTexture_0.Sample(gLinearSampler, input.uv);
    
    return color;
}