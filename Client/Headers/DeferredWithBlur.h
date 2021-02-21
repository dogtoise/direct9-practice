#pragma once

#include "IDemo.h"

class DeferredWithBlur : public IDemo
{
public:
	DeferredWithBlur();
	~DeferredWithBlur();



	// Inherited via IDemo
	virtual void Setup() override;

	virtual void Cleanup() override;

	virtual void Display() override;

private :
	void DeferredPipeline();

	void SetGBufferMRT();
	void SetLightMRT();
	void SetOriginMRT();

	void DrawCube(class ShadedCube* cube, float x, float y, float z, D3DXVECTOR4 diffuse);
	void DrawBlurCube(class ShadedCube* cube, float x, float y, float z, D3DXVECTOR4 diffuse);
	void DrawAmbient();
	void DrawLight();
	void DrawBlur();

private :
	std::vector<D3DLIGHT9> lights;

	class ShadedQuad* lightScreen;
	class ShadedQuad* blurScreen;
	
	std::vector<ShadedCube*> cubes;
	std::vector<D3DXVECTOR3> randomPos;

	LPD3DXEFFECT DeferredShader = nullptr;
	LPD3DXEFFECT PointLightShader = nullptr;
	LPD3DXEFFECT AmbientLightShader = nullptr;
	LPD3DXEFFECT DirectionalLightShader = nullptr;
	LPD3DXEFFECT BlurShader = nullptr;

	IDirect3DTexture9* cubeTexture;

	IDirect3DSurface9* originSurface;

	IDirect3DTexture9* depthRTTexture;
	IDirect3DSurface9* depthRTSurface;

	IDirect3DTexture9* albedoRTTexture;
	IDirect3DSurface9* albedoRTSurface;

	IDirect3DTexture9* normalRTTexture;
	IDirect3DSurface9* normalRTSurface;

	IDirect3DTexture9* blurMaskRTTexture;
	IDirect3DSurface9* blurMaskRTSurface;

	IDirect3DTexture9* lightRTTexture;
	IDirect3DSurface9* lightRTSurface;

	IDirect3DTexture9* stashRTTexture = 0;
	IDirect3DSurface9* stashRTSurface = 0;

};

