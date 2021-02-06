#include "stdafx.h"
#include "..\Headers\PSMultiTexture.h"
#include "VertexTypes.h"

PSMultiTexture::PSMultiTexture()
{
}


PSMultiTexture::~PSMultiTexture()
{
}

void PSMultiTexture::Setup()
{
	// Create geometry

	DEVICE->CreateVertexBuffer
	(
		6 * sizeof(MultiTexVertex),
		D3DUSAGE_WRITEONLY, 
		MultiTexVertex::FVF,
		D3DPOOL_MANAGED,
		&quadVB,
		0
	);

	MultiTexVertex * vertices = 0;
	quadVB->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = MultiTexVertex(-10.0f, -10.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	vertices[1] = MultiTexVertex(-10.0f, 10.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	vertices[2] = MultiTexVertex(10.0f, 10.0f, 5.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

	vertices[3] = MultiTexVertex(-10.0f, -10.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	vertices[4] = MultiTexVertex(10.0f, 10.0f, 5.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	vertices[5] = MultiTexVertex(10.0f, -10.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);


	quadVB->Unlock();

	// compile shader

	ID3DXBuffer *shader = nullptr;
	ID3DXBuffer *errorBuffer = nullptr;

	HRESULT hr = D3DXCompileShaderFromFile
	(
		L"../../Shaders/MultiTexturePS.hlsl",
		0,
		0,
		"Main",
		"ps_2_0",
		D3DXSHADER_DEBUG,
		&shader,
		&errorBuffer,
		&multiTexConstantTable
	);

	if (errorBuffer)
	{
		::MessageBox(0, (LPCTSTR)errorBuffer->GetBufferPointer(), 0, 0);
		errorBuffer->Release();
		assert(false);
	}
	if (FAILED(hr))
	{
		::MessageBox(0, L"D3DXCompileShaderFromFile() - FAILED", 0, 0);
		assert(false);
	}

	// Create pixel shader

	hr = DEVICE->CreatePixelShader
	(
		(DWORD*)shader->GetBufferPointer(),
		&multiTexPS
	);
	
	if (FAILED(hr))
	{
		::MessageBox(0, L"CreateVertexShader - FAILED", 0, 0);
		assert(false);
	}

	shader->Release();


	// load textures.
	D3DXCreateTextureFromFile(DEVICE, L"../../Resources/crate.jpg", &baseTex);
	D3DXCreateTextureFromFile(DEVICE, L"../../Resources/spotlight.bmp", &spotLightTex);
	D3DXCreateTextureFromFile(DEVICE, L"../../Resources/text.bmp", &stringTex);
	//D3DXCreateTextureFromFile(DEVICE, L"../../Resources/spotlight.bmp", &stringTex);

	// set projection matrix

	D3DXMATRIX P;
	D3DXMatrixPerspectiveFovLH(
		&P, D3DX_PI * 0.25f,
		(float)WIN_WIDTH / (float)WIN_HEIGHT, 1.0f, 1000.0f);

	DEVICE->SetTransform(D3DTS_PROJECTION, &P);


	// disable lighting
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);

	// get handles

	baseTexHandle = multiTexConstantTable->GetConstantByName(0,"baseTex");
	spotLightTexHandle = multiTexConstantTable->GetConstantByName(0, "spotLightTex");
	stringTexHandle = multiTexConstantTable->GetConstantByName(0, "stringTex");


	// set constant description 

	UINT count;

	multiTexConstantTable->GetConstantDesc(baseTexHandle, &baseTexDesc, &count);
	multiTexConstantTable->GetConstantDesc(spotLightTexHandle, &spotLightTexDesc, &count);
	multiTexConstantTable->GetConstantDesc(stringTexHandle, &stringTexDesc, &count);

	multiTexConstantTable->SetDefaults(DEVICE);
}

void PSMultiTexture::Cleanup()
{
	quadVB->Release();

	baseTex->Release();
	spotLightTex->Release();
	stringTex->Release();

	multiTexPS->Release();
	multiTexConstantTable->Release();
}

void PSMultiTexture::Display()
{
	static float angle = (3.0f * D3DX_PI) / 2.0f;
	static float radius = 20.0f;

	if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
		angle -= 0.005f;

	if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
		angle += 0.005f;

	if (::GetAsyncKeyState(VK_UP) & 0x8000f)
		radius -= 0.02f;

	if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
		radius += 0.02f;

	D3DXVECTOR3 position(cosf(angle) * radius, 0.0f, sinf(angle) * radius);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V; 
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	DEVICE->SetTransform(D3DTS_VIEW, &V);


	// render

	DEVICE->SetPixelShader(multiTexPS);
	DEVICE->SetFVF(MultiTexVertex::FVF);
	DEVICE->SetStreamSource(0, quadVB, 0, sizeof(MultiTexVertex));

	// base tex
	DEVICE->SetTexture(baseTexDesc.RegisterIndex, baseTex);
	DEVICE->SetSamplerState(baseTexDesc.RegisterIndex, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(baseTexDesc.RegisterIndex, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(baseTexDesc.RegisterIndex, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// spotlight tex
	DEVICE->SetTexture(spotLightTexDesc.RegisterIndex, spotLightTex);
	DEVICE->SetSamplerState(spotLightTexDesc.RegisterIndex, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(spotLightTexDesc.RegisterIndex, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(spotLightTexDesc.RegisterIndex, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// string tex
	DEVICE->SetTexture(stringTexDesc.RegisterIndex, stringTex);
	DEVICE->SetSamplerState(stringTexDesc.RegisterIndex, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(stringTexDesc.RegisterIndex, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(stringTexDesc.RegisterIndex, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);


}
