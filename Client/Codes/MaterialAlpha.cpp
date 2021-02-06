#include "stdafx.h"
#include "..\Headers\MaterialAlpha.h"
#include "VertexTypes.h"
#include "MaterialHelper.h"
#include "LightHelper.h"

MaterialAlpha::MaterialAlpha()
{
}


MaterialAlpha::~MaterialAlpha()
{
}

void MaterialAlpha::Setup()
{
	teapotMaterial = MaterialHelper::RED_MTRL;
	// set alpha to 50% opacity
	teapotMaterial.Diffuse.a = 0.5f;

	backGroundMaterial = MaterialHelper::WHITE_MTRL;

	// create the teapot

	D3DXCreateTeapot(DEVICE, &teapot, 0);

	// Create the background quad.

	DEVICE->CreateVertexBuffer
	(
		6 * sizeof(TextureVertex),
		D3DUSAGE_WRITEONLY,
		TextureVertex::FVF,
		D3DPOOL_MANAGED,
		&backGroundQuadBuffer,
		0
	);

	TextureVertex* vertices;
	backGroundQuadBuffer->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = TextureVertex(-10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vertices[1] = TextureVertex(-10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	vertices[2] = TextureVertex(10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	vertices[3] = TextureVertex(-10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vertices[4] = TextureVertex(10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	vertices[5] = TextureVertex(10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	backGroundQuadBuffer->Unlock();

	// setup a directional light
	D3DLIGHT9 dir;
	::ZeroMemory(&dir, sizeof(dir));
	dir.Type = D3DLIGHT_DIRECTIONAL;
	dir.Diffuse = WHITE;
	dir.Specular = WHITE * 0.2f;
	dir.Ambient = WHITE * 0.6f;
	dir.Direction = D3DXVECTOR3(0.707f, 0.0f, 0.707f);

	DEVICE->SetLight(0, &dir);
	DEVICE->LightEnable(0, true);

	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);

	D3DXCreateTextureFromFile(
		DEVICE,
		L"../../Resources/crate.jpg",
		&backGroundTexture);

	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// use alpha in material's diffuse component for alpha
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//
	// Set camera.
	//

	D3DXVECTOR3 pos(0.0f, 0.0f, -3.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &pos, &target, &up);

	DEVICE->SetTransform(D3DTS_VIEW, &viewMatrix);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f, // 90 - degree
		(float)WIN_WIDTH / (float)WIN_HEIGHT,
		1.0f,
		1000.0f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);
}

void MaterialAlpha::Cleanup()
{
	backGroundQuadBuffer->Release();
	teapot->Release();
	backGroundTexture->Release();
}

void MaterialAlpha::Display()
{
	if (::GetAsyncKeyState('A') & 0x8000f)
		teapotMaterial.Diffuse.a += 0.01f;
	if (::GetAsyncKeyState('S') & 0x8000f)
		teapotMaterial.Diffuse.a -= 0.01f;

	if (teapotMaterial.Diffuse.a > 1.0f)
		teapotMaterial.Diffuse.a = 1.0f;
	if (teapotMaterial.Diffuse.a < 0.0f)
		teapotMaterial.Diffuse.a = 0.0f;

	// draw background quad
	D3DXMATRIX worldMatrix;
	D3DXMatrixIdentity(&worldMatrix);
	DEVICE->SetTransform(D3DTS_WORLD, &worldMatrix);
	DEVICE->SetFVF(TextureVertex::FVF);
	DEVICE->SetStreamSource(0, backGroundQuadBuffer, 0, sizeof(TextureVertex));
	DEVICE->SetMaterial(&backGroundMaterial);
	DEVICE->SetTexture(0, backGroundTexture);

	// draw the teapot
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	D3DXMatrixScaling(&worldMatrix, 1.5f, 1.5f, 1.5f);
	DEVICE->SetTransform(D3DTS_WORLD, &worldMatrix);
	DEVICE->SetMaterial(&teapotMaterial);
	DEVICE->SetTexture(0, 0);
	teapot->DrawSubset(0);

	// change to default state.
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

}
