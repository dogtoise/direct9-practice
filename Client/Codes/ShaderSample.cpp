#include "stdafx.h"
#include "ShaderSample.h"
#include "ShadedCube.h"



ShaderSample::ShaderSample()
{
}


ShaderSample::~ShaderSample()
{
}

void ShaderSample::Setup()
{
	HRESULT hr = 0;

	shadedCube = new ShadedCube();

	D3DXCreateTextureFromFile(
		DEVICE,
		L"../../Resources/crate.jpg",
		&texture);

	ID3DXBuffer* vsShader = nullptr;
	ID3DXBuffer* vsErrorBuffer = nullptr;
	ID3DXBuffer* psShader = nullptr;
	ID3DXBuffer* psErrorBuffer = nullptr;

	hr = D3DXCompileShaderFromFile
	(
		L"../../Shaders/TestVS.hlsl",
		0,
		0,
		"main",
		"vs_2_0",
		D3DXSHADER_DEBUG,
		&vsShader,
		&vsErrorBuffer,
		&vsConstantTable
	);

	if (vsErrorBuffer)
	{
		MessageBoxA(0, (char*)vsErrorBuffer->GetBufferPointer(), 0, 0);

		assert(false);
	}
	assert(SUCCEEDED(hr));

	hr = DEVICE->CreateVertexShader
	(
		(DWORD*)vsShader->GetBufferPointer(),
		&vsTestShader
	);
	assert(SUCCEEDED(hr));

	hr = D3DXCompileShaderFromFile
	(
		L"../../Shaders/TestPS.hlsl",
		0,
		0,
		"main",
		"ps_2_0",
		D3DXSHADER_DEBUG,
		&psShader,
		&psErrorBuffer,
		&psConstantTable
	);

	if (psErrorBuffer)
	{
		MessageBoxA(0, (char*)psErrorBuffer->GetBufferPointer(), 0, 0);

		assert(false);
	}
	assert(SUCCEEDED(hr));

	hr = DEVICE->CreatePixelShader
	(
		(DWORD*)psShader->GetBufferPointer(),
		&psTestShader
	);
	assert(SUCCEEDED(hr));

	WorldMatrixHandle = vsConstantTable->GetConstantByName(0, "WorldMatrix");
	ViewMatrixHandle = vsConstantTable->GetConstantByName(0, "ViewMatrix");
	ProjMatrixHandle = vsConstantTable->GetConstantByName(0, "ProjMatrix");

	vsConstantTable->SetDefaults(DEVICE);

	DiffuseHandle = psConstantTable->GetConstantByName(0, "Diffuse");
	BaseMapHandle = psConstantTable->GetConstantByName(0, "BaseMap");

	UINT count;
	psConstantTable->GetConstantDesc(BaseMapHandle, &BaseMapDesc, &count);

	psConstantTable->SetDefaults(DEVICE); 

	D3DXMatrixPerspectiveFovLH(
		&projMatrix, D3DX_PI * 0.25f,
		(float)WIN_WIDTH / (float)WIN_HEIGHT, 1.0f, 1000.0f);

	D3DXVECTOR3 position(0, 2, -2);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);
}

void ShaderSample::Cleanup()
{
}

void ShaderSample::Display()
{
	DEVICE->SetStreamSource(0, shadedCube->_vb, 0, shadedCube->vertexSize);
	DEVICE->SetVertexDeclaration(shadedCube->m_pDeclare);
	DEVICE->SetIndices(shadedCube->_ib);

	D3DXMATRIX yRot;

	static float y = 0.0f;

	D3DXMatrixRotationY(&yRot, y);
	y += 0.001f;

	if (y >= 6.28f)
		y = 0.0f;


		vsConstantTable->SetMatrix(DEVICE, WorldMatrixHandle, &yRot);
	vsConstantTable->SetMatrix(DEVICE, ViewMatrixHandle, &viewMatrix);
	vsConstantTable->SetMatrix(DEVICE, ProjMatrixHandle, &projMatrix);


	D3DXVECTOR4 diffuse(255, 1, 0, 0);
	psConstantTable->SetVector(DEVICE, DiffuseHandle, &diffuse);
	DEVICE->SetTexture(BaseMapDesc.RegisterIndex, texture);

	DEVICE->SetVertexShader(vsTestShader);
	DEVICE->SetPixelShader(psTestShader);

	DEVICE->DrawIndexedPrimitive
	(
		D3DPT_TRIANGLELIST,
		0,
		0,
		24,
		0,
		12
	);


}
