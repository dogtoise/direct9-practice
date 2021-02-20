matrix WorldMatrix;
matrix ViewMatrix;
matrix ProjMatrix;
float4 Diffuse;

texture CubeTex;
sampler CubeSampler = sampler_state
{
	Texture = (CubeTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};
texture PositionTex;
sampler PositionSampler = sampler_state
{
	Texture = (PositionTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};
texture AlbedoTex;
sampler AlbedoSampler = sampler_state
{
	Texture = (AlbedoTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};
texture DiffuseTex;
sampler DiffuseSampler = sampler_state
{
	Texture = (DiffuseTex);
	MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = None;
    AddressU = clamp;
    AddressV = clamp;
};


void GBufferVS(
	float4 position : POSITION,
	float2 texcoord : TEXCOORD0,
	out float4 outPosition : POSITION,
	out float4 outPosForPS : TEXCOORD0,
	out float2 outTexcoord : TEXCOORD1
)
{
    outPosition = mul(position, WorldMatrix);
	outPosition = mul(outPosition, ViewMatrix);
	outPosition = mul(outPosition, ProjMatrix);

outPosForPS = outPosition;
	outTexcoord = texcoord;
}

void GBufferPS(
	float4 position : TEXCOORD0,
	float2 texcoord : TEXCOORD1,
	out float4 outPos : COLOR0,
	out float4 outAlbedo : COLOR1,
	out float4 outDiffuse : COLOR2
	)
{
	float4 baseColor = tex2D(CubeSampler, texcoord);
	
	outPos = position;
	outAlbedo = baseColor;
	outDiffuse = Diffuse;
}


void OutScreenVS(float4 position : POSITION,
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
float4 OutScreenPS(float2 texcoord : TEXCOORD0) : COLOR0
{
	//float4 defaultColor = tex2D(DefaultSampler, texcoord);
	float4 pos = tex2D(PositionSampler, texcoord);
	float4 albedo = tex2D(AlbedoSampler, texcoord);
	float4 diffuse = tex2D(DiffuseSampler, texcoord);

	
	//return float4(255, 255,255,255);
	return saturate(albedo + diffuse);
}
technique GBuffer
{
	pass P0
	{
		VertexShader = compile vs_3_0 GBufferVS();
		PixelShader = compile ps_3_0 GBufferPS();
	}
};

technique OutScreen
{
	pass P0
	{
		VertexShader = compile vs_3_0 OutScreenVS();
		PixelShader = compile ps_3_0 OutScreenPS();
	}
}