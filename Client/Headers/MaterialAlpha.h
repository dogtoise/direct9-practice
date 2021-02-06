#pragma once

#include "IDemo.h"


class MaterialAlpha : public IDemo
{
public:
	MaterialAlpha();
	~MaterialAlpha();

	// Inherited via IDemo
	virtual void Setup() override;
	virtual void Cleanup() override;
	virtual void Display() override;

private :
	ID3DXMesh* teapot = nullptr;
	D3DMATERIAL9 teapotMaterial;

	IDirect3DVertexBuffer9* backGroundQuadBuffer = nullptr;
	IDirect3DTexture9 * backGroundTexture = nullptr;
	D3DMATERIAL9 backGroundMaterial;

};

