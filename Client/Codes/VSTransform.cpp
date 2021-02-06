#include "stdafx.h"
#include "..\Headers\VSTransform.h"


VSTransform::VSTransform()
{
}


VSTransform::~VSTransform()
{
}

void VSTransform::Setup()
{
	HRESULT hr = 0;

	D3DXCreateTeapot(DEVICE, &teapotMesh, 0);

	ID3DXBuffer* shader = nullptr;
	ID3DXBuffer* errorBuffer = nullptr;

	hr = D3DXCompileShaderFromFile(
		L"../../Shaders/TransformShader.hlsl",
		0,
		0,
		"Main",  // entry point function name
		"vs_1_1",// shader version to compile to
		D3DXSHADER_DEBUG,
		&shader,
		&errorBuffer,
		&transformConstantTable);

	if (errorBuffer)
	{
		MessageBox(0, (LPCWSTR)errorBuffer->GetBufferPointer(), 0, 0);
		errorBuffer->Release();
	}
	assert(SUCCEEDED(hr));

	hr = DEVICE->CreateVertexShader
	(
		(DWORD*)shader->GetBufferPointer(),
		&transformShader
	);
	assert(SUCCEEDED(hr));

	shader->Release();


	// get handle
	transformViewProjHandle = transformConstantTable->GetConstantByName(0, "ViewProjMatrix");
	
	// set shader constants
	transformConstantTable->SetDefaults(DEVICE);

	// set proj matrix
	D3DXMatrixPerspectiveFovLH(
		&projMatrix, D3DX_PI * 0.25f,
		(float)WIN_WIDTH / (float)WIN_HEIGHT, 1.0f, 1000.0f);

	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

}

void VSTransform::Cleanup()
{
	teapotMesh->Release();
	transformShader->Release();
	transformConstantTable->Release();
}

void VSTransform::Display()
{

	static float angle = (3.0f * D3DX_PI) / 2.0f;
	static float height = 5.0f;

	if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
		angle -= 0.005f;

	if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
		angle += 0.005f;

	if (::GetAsyncKeyState(VK_UP) & 0x8000f)
		height += 0.05f ;

	if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
		height -= 0.05f ;

	D3DXVECTOR3 position(cosf(angle) * 10.0f, height, sinf(angle) * 10.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);

	D3DXMATRIX viewProj = viewMatrix * projMatrix;

	transformConstantTable->SetMatrix(DEVICE, transformViewProjHandle, &viewProj);

	DEVICE->SetVertexShader(transformShader);

	teapotMesh->DrawSubset(0);


}
