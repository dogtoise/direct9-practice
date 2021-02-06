#pragma once
#include "IDemo.h"
class MeshesDemo : public IDemo
{
public:
	MeshesDemo();
	~MeshesDemo();


	// Inherited via IDemo
	virtual void Setup() override;

	virtual void Cleanup() override;

	virtual void Display() override;

private :
	
	ID3DXMesh* Objects[5] = { 0, 0, 0, 0, 0 };

	D3DXMATRIX ObjWorldMatrices[5];
};

