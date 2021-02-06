#pragma once
#include "IDemo.h"

class LitPyramid : public IDemo
{ 
public:
	LitPyramid();
	~LitPyramid();

	// Inherited via IDemo
	virtual void Setup() override;

	virtual void Cleanup() override;

	virtual void Display() override;

private : 
	IDirect3DVertexBuffer9 * pyramidBuffer = nullptr;

};

