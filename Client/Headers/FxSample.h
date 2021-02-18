#pragma once

#include "IDemo.h"

class FxSample : public IDemo
{
public:
	FxSample();
	~FxSample();

	// Inherited via IDemo
	virtual void Setup() override;
	virtual void Cleanup() override;
	virtual void Display() override;

private :
	class ShadedCube* shadedCube;

	LPD3DXEFFECT m_pEffect = nullptr;

	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	IDirect3DTexture9* texture;
};

