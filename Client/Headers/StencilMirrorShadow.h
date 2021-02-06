#pragma once

#include "IDemo.h"

// TODO
class StencilMirrorShadow : public IDemo
{
public:
	StencilMirrorShadow();
	~StencilMirrorShadow();

	// Inherited via IDemo
	virtual void Setup() override;
	virtual void Cleanup() override;
	virtual void Display() override;

private :
	IDirect3DVertexBuffer9 * vb = nullptr;

	IDirect3DTexture9 *floorTex = nullptr;
	IDirect3DTexture9 *wallTex = nullptr;
	IDirect3DTexture9 *mirrorTex = nullptr;

	D3DMATERIAL9 floorMaterial;
	D3DMATERIAL9 wallMaterial;
	D3DMATERIAL9 mirrorMaterial;

	ID3DXMesh* teapotMesh = nullptr;
	D3DXVECTOR3 teapotPosition = { 0.0f, 3.0f, -7.5f };
	D3DMATERIAL9 teapotMaterial;

	void RenderScene();
	void RenderMirror();
	void RenderShadow();
};

