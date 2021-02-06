#pragma once
#include "IDemo.h"

class ColorTriangle : public IDemo
{
public:
	ColorTriangle();
	~ColorTriangle();

	// Inherited via IDemo
	virtual void Setup() override;
	virtual void Cleanup() override;
	virtual void Display() override;

private :
	IDirect3DVertexBuffer9* triangleBuffer = 0;
	D3DXMATRIX WorldMatrix;
};

