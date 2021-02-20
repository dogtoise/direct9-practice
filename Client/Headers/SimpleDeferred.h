#pragma once

#include "IDemo.h"

class SimpleDeferred : public IDemo
{
public:
	SimpleDeferred();
	~SimpleDeferred();



	// Inherited via IDemo
	virtual void Setup() override;

	virtual void Cleanup() override;

	virtual void Display() override;

private :
	void DeferredPipeline();
	void SetMRT();
	void ResumeMRT();

	void DrawCube(class ShadedCube* cube, float x, float y, float z, D3DXVECTOR4 diffuse);
	void DrawResult();
private:
	class ShadedQuad* resultScreen;

	class ShadedCube * leftCube;
	class ShadedCube* rightCube;

	LPD3DXEFFECT m_pEffect = nullptr;

	IDirect3DTexture9* cubeTexture;

	IDirect3DSurface9* originSurface;

	IDirect3DTexture9* positionRTTexture;
	IDirect3DSurface9* positionRTSurface;

	IDirect3DTexture9* albedoRTTexture;
	IDirect3DSurface9* albedoRTSurface;

	IDirect3DTexture9* diffuseRTTexture;
	IDirect3DSurface9* diffuseRTSurface;

	D3DFORMAT texFormat = D3DFMT_A8R8G8B8;


};

