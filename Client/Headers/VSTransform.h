#pragma once

#include "IDemo.h"


class VSTransform : public IDemo
{
public:
	VSTransform();
	~VSTransform();


	// Inherited via IDemo
	virtual void Setup() override;

	virtual void Cleanup() override;

	virtual void Display() override;

private :
	IDirect3DVertexShader9* transformShader;
	ID3DXConstantTable* transformConstantTable;

	ID3DXMesh * teapotMesh;

	D3DXHANDLE transformViewProjHandle = 0;

	D3DXMATRIX projMatrix;



};

