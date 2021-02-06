#pragma once
#include "IDemo.h"


class TexCube : public IDemo
{
public:
	TexCube();
	~TexCube();

	// Inherited via IDemo
	virtual void Setup() override;
	virtual void Cleanup() override;
	virtual void Display() override;

private : 
	class Cube* box = nullptr;
	IDirect3DTexture9* texture = nullptr;
};

