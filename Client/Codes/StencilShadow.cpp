#include "stdafx.h"
#include "..\Headers\StencilShadow.h"
#include "VertexTypes.h"
#include "LightHelper.h"
#include "MaterialHelper.h"

StencilShadow::StencilShadow()
{
}


StencilShadow::~StencilShadow()
{
}

void StencilShadow::Setup()
{
	floorMaterial = MaterialHelper::WHITE_MTRL;
	wallMaterial = MaterialHelper::WHITE_MTRL;
	mirrorMaterial = MaterialHelper::WHITE_MTRL;
	teapotMaterial = MaterialHelper::YELLOW_MTRL;

	wallMaterial.Specular = WHITE * 0.2f;

	// create the teapot 
	D3DXCreateTeapot(DEVICE, &teapotMesh, 0);

	//
	// Create and specify geometry.  For this sample we draw a floor
	// and a wall with a mirror on it.  We put the floor, wall, and
	// mirror geometry in one vertex buffer.
	//
	//   |----|----|----|
	//   |Wall|Mirr|Wall|
	//   |    | or |    |
	//   /--------------/
	//  /   Floor      /
	// /--------------/
	//
	DEVICE->CreateVertexBuffer
	(
		24 * sizeof(TextureVertex),
		0, // usage
		TextureVertex::FVF,
		D3DPOOL_MANAGED,
		&vb,
		0
	);
	
	TextureVertex* vertices = nullptr;
	vb->Lock(0, 0, (void**)&vertices, 0);


	// floor
	vertices[0] = TextureVertex(-7.5f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	vertices[1] = TextureVertex(-7.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	vertices[2] = TextureVertex(7.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

	vertices[3] = TextureVertex(-7.5f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	vertices[4] = TextureVertex(7.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	vertices[5] = TextureVertex(7.5f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

	// wall
	vertices[6] = TextureVertex(-7.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vertices[7] = TextureVertex(-7.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	vertices[8] = TextureVertex(-2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	vertices[9] = TextureVertex(-7.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vertices[10] = TextureVertex(-2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	vertices[11] = TextureVertex(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// Note: We leave gap in middle of walls for mirror

	vertices[12] = TextureVertex(2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vertices[13] = TextureVertex(2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	vertices[14] = TextureVertex(7.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	vertices[15] = TextureVertex(2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vertices[16] = TextureVertex(7.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	vertices[17] = TextureVertex(7.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// mirror
	vertices[18] = TextureVertex(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vertices[19] = TextureVertex(-2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	vertices[20] = TextureVertex(2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	vertices[21] = TextureVertex(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vertices[22] = TextureVertex(2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	vertices[23] = TextureVertex(2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	vb->Unlock();

	// load texture, set filters.
	D3DXCreateTextureFromFile(DEVICE, L"../../Resources/checker.jpg", &floorTex);
	D3DXCreateTextureFromFile(DEVICE, L"../../Resources/brick0.jpg", &wallTex);
	D3DXCreateTextureFromFile(DEVICE, L"../../Resources/ice.bmp", &mirrorTex);

	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// light
	D3DXVECTOR3 lightDir(0.707f, -0.707f, 0.707f);
	D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);
	D3DLIGHT9 light =LightHelper::InitDirectionalLight(&lightDir, &color);

	DEVICE->SetLight(0, &light);
	DEVICE->LightEnable(0, true);

	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);

	// set camera
	D3DXVECTOR3    pos(-10.0f, 3.0f, -15.0f);
	D3DXVECTOR3 target(0.0, 0.0f, 0.0f);
	D3DXVECTOR3     up(0.0f, 1.0f, 0.0f);

	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &pos, &target, &up);

	DEVICE->SetTransform(D3DTS_VIEW, &V);

	//
	// Set projection matrix.
	//
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI / 4.0f, // 45 - degree
		(float)WIN_WIDTH / (float)WIN_HEIGHT,
		1.0f,
		1000.0f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);
}

void StencilShadow::Cleanup()
{
	vb->Release();
	floorTex->Release();
	wallTex->Release();
	mirrorTex->Release();
	teapotMesh->Release();
}

void StencilShadow::Display()
{
	static float radius = 20.0f;

	if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
		teapotPosition.x -= 0.03f;

	if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
		teapotPosition.x += 0.03f;

	if (::GetAsyncKeyState(VK_UP) & 0x8000f)
		radius -= 0.02f;

	if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
		radius += 0.02f ;


	static float angle = (3.0f * D3DX_PI) / 2.0f;

	if (::GetAsyncKeyState('A') & 0x8000f)
		angle -= 0.005f;

	if (::GetAsyncKeyState('S') & 0x8000f)
		angle += 0.005f;


	D3DXVECTOR3 position(cosf(angle) * radius, 3.0f, sinf(angle) * radius);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	DEVICE->SetTransform(D3DTS_VIEW, &V);

	RenderScene();
	RenderShadow();


}

void StencilShadow::RenderScene()
{
	// draw teapot mesh
	DEVICE->SetMaterial(&teapotMaterial);
	DEVICE->SetTexture(0, 0);
	D3DXMATRIX W;
	D3DXMatrixTranslation(&W,
		teapotPosition.x,
		teapotPosition.y,
		teapotPosition.z);

	DEVICE->SetTransform(D3DTS_WORLD, &W);
	teapotMesh->DrawSubset(0);

	D3DXMATRIX identityMatrix;
	D3DXMatrixIdentity(&identityMatrix);
	DEVICE->SetTransform(D3DTS_WORLD, &identityMatrix);

	DEVICE->SetStreamSource(0, vb, 0, sizeof(TextureVertex));
	DEVICE->SetFVF(TextureVertex::FVF);

	// draw the floor
	DEVICE->SetMaterial(&floorMaterial);
	DEVICE->SetTexture(0, floorTex);
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	// draw the walls
	DEVICE->SetMaterial(&wallMaterial);
	DEVICE->SetTexture(0, wallTex);
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 6, 4);

	// draw the mirror
	DEVICE->SetMaterial(&mirrorMaterial);
	DEVICE->SetTexture(0, mirrorTex);
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 18, 2);




}

void StencilShadow::RenderShadow()
{
	DEVICE->SetRenderState(D3DRS_STENCILENABLE, true);
	DEVICE->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	DEVICE->SetRenderState(D3DRS_STENCILREF, 0x0);
	DEVICE->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	DEVICE->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
	DEVICE->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	DEVICE->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

	// position shadow
	D3DXVECTOR4 lightDirection(0.707f, -0.707f, 0.707f, 0.0f);
	D3DXPLANE groundPlane(0.0f, -1.0f, 0.0f, 0.0f);


	// TODO : ??
	D3DXMATRIX shadowMatrix;
	D3DXMatrixShadow
	(
		&shadowMatrix,
		&lightDirection,
		&groundPlane
	);

	D3DXMATRIX teapotMatrix;
	D3DXMatrixTranslation
	(
		&teapotMatrix,
		teapotPosition.x,
		teapotPosition.y,
		teapotPosition.z
	);

	// TODO : ??
	D3DXMATRIX worldMatrix = teapotMatrix * shadowMatrix;
	
	DEVICE->SetTransform(D3DTS_WORLD, &worldMatrix);

	// alpha blend the shadow
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	D3DMATERIAL9 material = MaterialHelper::InitMaterial(BLACK, BLACK, BLACK, BLACK, 0.0f);
	material.Diffuse.a = 0.5f; // 50% transparency.

	// Disable depth buffer so that z-fighting doesn't occur when we
	// render the shadow on top of the floor.
	DEVICE->SetRenderState(D3DRS_ZENABLE, false);

	DEVICE->SetMaterial(&material);
	DEVICE->SetTexture(0, 0);
	teapotMesh->DrawSubset(0);

	DEVICE->SetRenderState(D3DRS_ZENABLE, true);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	DEVICE->SetRenderState(D3DRS_STENCILENABLE, false);


}
