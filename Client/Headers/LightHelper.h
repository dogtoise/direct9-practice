#pragma once
class LightHelper
{
public:
	LightHelper();
	~LightHelper();

	static D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color)
	{
		D3DLIGHT9 light;
		::ZeroMemory(&light, sizeof(light));

		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Ambient = *color * 0.6f;
		light.Diffuse = *color;
		light.Specular = *color * 0.6f;
		light.Direction = *direction;

		return light;
	}
};

