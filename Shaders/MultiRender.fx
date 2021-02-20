matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;
float4 Diffuse;

sampler2D BaseMap;
sampler2D DefaultMap;
sampler2D AlphaMap;

float4 gaussFilter[7] =  {
	 -3.0, 0.0, 0.0, 1.0/64.0, 
	 -2.0, 0.0, 0.0, 6.0/64.0,
	 -1.0, 0.0, 0.0, 15.0/64.0, 
	0.0, 0.0, 0.0, 20.0/64.0,
	1.0, 0.0, 0.0, 15.0/64.0,
	2.0, 0.0, 0.0, 6.0/64.0,
	3.0, 0.0, 0.0, 1.0/64.0
	};
	float texScaler = 1.0/128.0;
	float texOffset = 0.0;

void DefaultVS(
	float4 position : POSITION,
	float2 texcoord : TEXCOORD0,
	out float4 outPosition : POSITION,
	out float2 outTexcoord : TEXCOORD0
)
{
	
	outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

	outTexcoord = texcoord;
}

float4 DefaultPS(float2 texcoord : TEXCOORD0) : COLOR0
{
	float4 baseColor = tex2D(BaseMap, texcoord);

	return saturate(baseColor + Diffuse);
}

void AlphaDrawVS(
	float4 position : POSITION,
	float2 texcoord : TEXCOORD0,
	out float4 outPosition : POSITION,
	out float2 outTexcoord : TEXCOORD0
)
{
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(position, ViewMatrix);
	outPosition = mul(position, ProjMatrix);

	outTexcoord = texcoord;
}

float4 AlphaDrawPS(float2 texcoord : TEXCOORD0) : COLOR0
{
	float4 baseColor = tex2D(BaseMap, texcoord);

	return baseColor.w;
}

void GaussVS(float4 position : POSITION,
	float2 texcoord : TEXCOORD0,
	out float4 outPosition : POSITION,
	out float2 outTexcoord : TEXCOORD0
)
{
 outPosition = mul(position, WorldMatrix);
	outPosition = mul(position, ViewMatrix);
	outPosition = mul(position, ProjMatrix);

	outTexcoord = texcoord;
}
float4 GaussPS(float2 texcoord : TEXCOORD0) : COLOR0
{
	float4 color = 0.0;
	float4 originColor = tex2D(BaseMap, texcoord);


	for(int i = 0; i < 7; i++)
	{
		float alpha = tex2D(AlphaMap, float2(texcoord.x + gaussFilter[i].x 
		* texScaler + texOffset,
		texcoord.y + gaussFilter[i].y * texScaler + texOffset ));


		color += tex2D(BaseMap, float2(texcoord.x + gaussFilter[i].x 
		* texScaler + texOffset,
		texcoord.y + gaussFilter[i].y * texScaler + texOffset )) * gaussFilter[i].w * alpha;
	} 

	return originColor;
}

void MergeVS(float4 position : POSITION,
	float2 texcoord : TEXCOORD0,
	out float4 outPosition : POSITION,
	out float2 outTexcoord : TEXCOORD0
)
{
	outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

	outTexcoord = texcoord;
}
float4 MergePS(float2 texcoord : TEXCOORD0) : COLOR0
{
	float4 defaultColor = tex2D(DefaultMap, texcoord);
	//return float4(255, 255,255,255);
	return saturate(defaultColor + Diffuse);
}

technique Default_Technique
{
	pass P0
	{
		VertexShader = compile vs_3_0 DefaultVS();
		PixelShader = compile ps_3_0 DefaultPS();
	}
};
technique Alpha_Technique
{
	pass P0
	{
		VertexShader = compile vs_3_0 AlphaDrawVS();
		PixelShader = compile ps_3_0 AlphaDrawPS();
	}
}
technique Gauss_Technique
{
	pass P0
	{
		VertexShader = compile vs_3_0 GaussVS();
		PixelShader = compile ps_3_0 GaussPS();
	}
}
technique Merge_Technique
{
	pass P0
	{
		VertexShader = compile vs_3_0 MergeVS();
		PixelShader = compile ps_3_0 MergePS();
	}
}