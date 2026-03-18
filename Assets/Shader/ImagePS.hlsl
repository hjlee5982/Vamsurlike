#include "CBuffer.hlsli"
#include "Struct.hlsli"

float4 main(PS_IN_UI input) : SV_TARGET
{
    float4 color = gTexture_0.Sample(gLinearSampler, input.uv);
    
    return UIColor;
}