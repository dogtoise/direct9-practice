#pragma once

#include "IDemo.h"


class TextureAlpha : public IDemo
{
public:
	TextureAlpha();
	~TextureAlpha();

	// Inherited via IDemo
	virtual void Setup() override;
	virtual void Cleanup() override;
	virtual void Display() override;

private :
	IDirect3DTexture9* crateTex = nullptr;
	class Cube* box = nullptr;
	D3DXMATRIX boxWorldMatrix;

	IDirect3DVertexBuffer9* backDropVB = nullptr;
	IDirect3DTexture9* backDropTexture = nullptr;

};

