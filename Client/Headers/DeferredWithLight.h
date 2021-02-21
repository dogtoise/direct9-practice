#pragma once

#include "IDemo.h"

class DeferredWithLight : public IDemo
{
public:
	DeferredWithLight();
	~DeferredWithLight();

	// Inherited via IDemo
	virtual void Setup() override;
	virtual void Cleanup() override;
	virtual void Display() override;

private :
	void DeferredPipeline();
	void SetMRT();
	void ResumeMRT();

	void DrawCube(class ShadedCube* cube, float x, float y, float z, D3DXVECTOR4 diffuse);
	void DrawAmbient();
	void DrawLight();

	void DrawResult();

private :
	std::vector<D3DLIGHT9> lights;
	
	class ShadedQuad* resultScreen;
	
	class ShadedCube* leftCube;
	class ShadedCube* rightCube;

	D3DXVECTOR3 eyePosition;

	LPD3DXEFFECT DeferredShader = nullptr;

	LPD3DXEFFECT PointLightShader = nullptr;

	IDirect3DTexture9* cubeTexture;

	IDirect3DSurface9* originSurface;

	IDirect3DTexture9* depthRTTexture;
	IDirect3DSurface9* depthRTSurface;

	IDirect3DTexture9* albedoRTTexture;
	IDirect3DSurface9* albedoRTSurface;
	
	IDirect3DTexture9* normalRTTexture;
	IDirect3DSurface9* normalRTSurface;

	IDirect3DTexture9* specularRTTextue;
	IDirect3DSurface9* specularRTSurface;

	IDirect3DTexture9* stashRTTexture = 0;
	IDirect3DSurface9* stashRTSurface = 0;

};

