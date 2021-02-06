// global






sampler baseTex;
sampler spotLightTex;
sampler stringTex;

struct PS_INPUT
{
	float2 base : TEXCOORD0;
	float2 spotlight : TEXCOORD1;
	float2 text : TEXCOORD2;
};

struct PS_OUTPUT
{
	vector diffuse : COLOR0;
};

PS_OUTPUT Main(PS_INPUT input)
{
	// zero out members of output
	PS_OUTPUT output = (PS_OUTPUT)0;

	// sample appropriate textures
	// vector = color on uv texcoord ( texel) 
	vector baseColor = tex2D(baseTex, input.base);
	vector spotLightColor = tex2D(spotLightTex, input.spotlight);
	vector stringColor = tex2D(stringTex, input.text);
	
	// combine texel colors
	vector color = baseColor * spotLightColor + stringColor;
	
	// increase the intensity of the pixel slightly
	color += 0.1f;

	// save the resulting pixel color
	//output.diffuse = color;
	//output.diffuse = 0xff0000ff;
	output.diffuse = color;
	return output;
}