#pragma once

#include "IDemo.h"

class MultiTextureRender : public IDemo
{
public:
	MultiTextureRender();
	~MultiTextureRender();



	// Inherited via IDemo
	virtual void Setup() override;

	virtual void Cleanup() override;

	virtual void Display() override;


private :
	class ShadedCube* shadedCubeA;
	class ShadedCube* shadedCubeB; // 블러 먹일 큐브
	class ShadedQuad* shadedQuad; // 화면크기 쿼드

	LPD3DXEFFECT m_pEffect = nullptr;

	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	IDirect3DTexture9* texture;

	IDirect3DTexture9* defaultRTTexture;
	IDirect3DSurface9* defaultRTSurface;

	IDirect3DTexture9* alphaRTTexture;
	IDirect3DSurface9* alphaRTSurface;

	IDirect3DTexture9* resultRTTexture;
	IDirect3DSurface9* resultRTSurface;

	IDirect3DSurface9* backSurf;


	D3DFORMAT texFormat = D3DFMT_A8R8G8B8;
};

