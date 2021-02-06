#pragma once

#include "IDemo.h"

class PSMultiTexture : public IDemo
{
public:
	PSMultiTexture();
	~PSMultiTexture();

	// Inherited via IDemo
	virtual void Setup() override;
	virtual void Cleanup() override;
	virtual void Display() override;

private :

	IDirect3DPixelShader9 * multiTexPS = nullptr;
	ID3DXConstantTable *multiTexConstantTable = nullptr;

	IDirect3DVertexBuffer9 *quadVB = nullptr;

	IDirect3DTexture9* baseTex = nullptr;
	IDirect3DTexture9* spotLightTex = nullptr;
	IDirect3DTexture9 *stringTex = nullptr;

	D3DXHANDLE baseTexHandle = 0;
	D3DXHANDLE spotLightTexHandle = 0;
	D3DXHANDLE stringTexHandle = 0;
	
	D3DXCONSTANT_DESC baseTexDesc;
	D3DXCONSTANT_DESC spotLightTexDesc;
	D3DXCONSTANT_DESC stringTexDesc;

	
};

