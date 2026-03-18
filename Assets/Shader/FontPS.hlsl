#include "CBuffer.hlsli"
#include "Struct.hlsli"

float4 main(PS_IN_UI input) : SV_TARGET
{
    float4 color = gTexture_0.Sample(gLinearSampler, input.uv);
    
    //if(color.a != 0)
    //{
    //    color.r = 1.f;
    //    color.g = 1.f;
    //    color.b = 1.f;
    //}
    
    return float4(input.color.rgb, input.color.a * color.a);
}