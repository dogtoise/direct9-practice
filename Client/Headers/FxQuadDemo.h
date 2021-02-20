#pragma once

#include "IDemo.h"

class FxQuadDemo : public IDemo
{
public:
	FxQuadDemo();
	~FxQuadDemo();



	// Inherited via IDemo
	virtual void Setup() override;

	virtual void Cleanup() override;

	virtual void Display() override;

private :
	class ShadedQuad* shadedQuad;

	LPD3DXEFFECT m_pEffect = nullptr;

	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	IDirect3DTexture9* defaultRTTexture;
	IDirect3DSurface9* defaultRTSurface;

	IDirect3DTexture9* texture;
};

