#pragma once
class MaterialHelper
{
public:
	MaterialHelper();
	~MaterialHelper();

	static D3DMATERIAL9 InitMaterial(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
	{
		D3DMATERIAL9 mtrl;
		mtrl.Ambient = a;
		mtrl.Diffuse = d;
		mtrl.Specular = s;
		mtrl.Emissive = e;
		mtrl.Power = p;
		return mtrl;
	}
	static const D3DMATERIAL9 WHITE_MTRL;
	static const D3DMATERIAL9 RED_MTRL;
	static const D3DMATERIAL9 GREEN_MTRL;
	static const D3DMATERIAL9 BLUE_MTRL; 
	static const D3DMATERIAL9 YELLOW_MTRL;
};

