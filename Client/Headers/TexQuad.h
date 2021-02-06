#pragma once

#include "IDemo.h"

class TexQuad : public IDemo
{
public:
	TexQuad();
	~TexQuad();

	// Inherited via IDemo
	virtual void Setup() override;
	virtual void Cleanup() override;
	virtual void Display() override;

private :
	IDirect3DVertexBuffer9 * quadBuffer = nullptr;
	IDirect3DTexture9 * texture = nullptr;
};

