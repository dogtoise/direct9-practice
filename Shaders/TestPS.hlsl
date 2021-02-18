float4 Diffuse;

sampler2D BaseMap;

struct PS_INPUT
{
	float2 texcoord : TEXCOORD0;
};

float4 main(PS_INPUT input) : COLOR0
{
	float4 baseColor = tex2D(BaseMap, input.texcoord);

	return saturate(baseColor + Diffuse);
}