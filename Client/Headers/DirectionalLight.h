#pragma once

#include "IDemo.h"
class DirectionalLight : public IDemo 
{
public:
	DirectionalLight();
	~DirectionalLight();

	// Inherited via IDemo
	virtual void Setup() override;
	virtual void Cleanup() override;
	virtual void Display() override;

private :
	ID3DXMesh* objects[4] = { 0, 0, 0, 0 };
	D3DXMATRIX worldMatrices[4];
	D3DMATERIAL9 materials[4];
};

