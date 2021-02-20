#pragma once
#include "IDemo.h"

class RTTSample : public IDemo
{
public:
	RTTSample();
	~RTTSample();



	// Inherited via IDemo
	virtual void Setup() override;

	virtual void Cleanup() override;

	virtual void Display() override;

private :
	class ShadedCube * shadedCube;
	class ShadedQuad* shadedQuad;

	LPD3DXEFFECT m_pEffect = nullptr;

	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	IDirect3DTexture9* texture;

	IDirect3DTexture9* defaultRTTexture;
	IDirect3DSurface9* defaultRTSurface;

	
	D3DFORMAT texFormat = D3DFMT_A8R8G8B8;
};

