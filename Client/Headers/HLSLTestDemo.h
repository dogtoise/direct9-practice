#pragma once

#include "IDemo.h"




class HLSLTestDemo : public IDemo
{
public:
	HLSLTestDemo();
	~HLSLTestDemo();

	// Inherited via IDemo
	virtual void Setup() override;
	virtual void Cleanup() override;
	virtual void Display() override;

private :

	class ShadedCube * shadedCube;
	IDirect3DVertexShader9* vsTestShader;
	IDirect3DPixelShader9* psTestShader = nullptr;

	
	ID3DXConstantTable* vsConstantTable;
	ID3DXConstantTable* psConstantTable;

	D3DXHANDLE WorldMatrixHandle = NULL;
	D3DXHANDLE ViewMatrixHandle = NULL;
	D3DXHANDLE ProjMatrixHandle = NULL;

	D3DXHANDLE DiffuseHandle = NULL;
	D3DXHANDLE BaseMapHandle = NULL;

	D3DXCONSTANT_DESC BaseMapDesc;



	LPD3DXEFFECT	m_pEffect = nullptr;



	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	IDirect3DTexture9* texture;
};

