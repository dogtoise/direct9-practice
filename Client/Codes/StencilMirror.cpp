#include "stdafx.h"
#include "..\Headers\StencilMirror.h"
#include "MaterialHelper.h"
#include "VertexTypes.h"
#include "LightHelper.h"

StencilMirror::StencilMirror()
{
}


StencilMirror::~StencilMirror()
{
}

void StencilMirror::Setup()
{
	floorMaterial = MaterialHelper::WHITE_MTRL;
	wallMaterial = MaterialHelper::WHITE_MTRL;
	mirrorMaterial = MaterialHelper::WHITE_MTRL;
	teapotMaterial = MaterialHelper::YELLOW_MTRL;

	// make walls have low specular reflectance - 20%
	wallMaterial.Specular = WHITE * 0.2f;

	// create the teapot
	D3DXCreateTeapot(DEVICE, &teapot, 0);

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

	// load textures, set filters.
	D3DXCreateTextureFromFile(DEVICE, L"../../Resources/checker.jpg", &floorTex);
	D3DXCreateTextureFromFile(DEVICE, L"../../Resources/brick0.jpg", &wallTex);
	D3DXCreateTextureFromFile(DEVICE, L"../../Resources/ice.bmp", &mirrorTex);

	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);


	// light
	D3DXVECTOR3 lightDir(0.707f, -0.707f, 0.707f);
	D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);
	D3DLIGHT9 light = LightHelper::InitDirectionalLight(&lightDir, &color);

	DEVICE->SetLight(0, &light);
	DEVICE->LightEnable(0, true);

	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);

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

void StencilMirror::Cleanup()
{
	vb->Release();
	floorTex->Release();
	wallTex->Release();
	mirrorTex->Release();
	teapot->Release();
}

void StencilMirror::Display()
{
	static float radius = 20.0f;

	if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
		teapotPosition.x -= 0.03f;

	if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
		teapotPosition.x += 0.03f;

	if (::GetAsyncKeyState(VK_UP) & 0x8000f)
		radius -= 0.02f;

	if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
		radius += 0.02f;

	static float angle = (3.0f * D3DX_PI) / 2.0f;

	if (::GetAsyncKeyState('A') & 0x8000f)
		angle -= 0.05f;

	if (::GetAsyncKeyState('S') & 0x8000f)
		angle += 0.05f;

	D3DXVECTOR3 position(cosf(angle) * radius, 3.0f, sinf(angle) * radius);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	DEVICE->SetTransform(D3DTS_VIEW, &V);


	RenderScene();
	RenderMirror();

}

void StencilMirror::RenderScene()
{
	// draw teapot
	DEVICE->SetMaterial(&teapotMaterial);
	DEVICE->SetTexture(0, 0);
	D3DXMATRIX worldMatrix;
	D3DXMatrixTranslation(&worldMatrix,
		teapotPosition.x,
		teapotPosition.y,
		teapotPosition.z);

	DEVICE->SetTransform(D3DTS_WORLD, &worldMatrix);
	teapot->DrawSubset(0);

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

void StencilMirror::RenderMirror()
{
	//
	// Draw Mirror quad to stencil buffer ONLY.  In this way
	// only the stencil bits that correspond to the mirror will
	// be on.  Therefore, the reflected teapot can only be rendered
	// where the stencil bits are turned on, and thus on the mirror 
	// only.
	//

	// stencil ���۸� �մϴ�.
	DEVICE->SetRenderState(D3DRS_STENCILENABLE, true);
	// Stencil ���Ⱑ �׻� �����ϵ��� �մϴ�.
	// ���Ⱑ ������ ��� stencil�� 0x1�� ������ �մϴ�.
	DEVICE->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	DEVICE->SetRenderState(D3DRS_STENCILREF, 0x1);
	DEVICE->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	DEVICE->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
	// depth test�� �����ϸ� pixel�� ���������� �ǹ��� �������� �ʿ� ����
	DEVICE->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	DEVICE->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	// depth/stencil test�� �����ϸ� stencil ���� ���� 0x1�� ��.
	// D3DSTENCILOP_REPLACE -> ���ٽǹ��� �׸��� ������(D3DRS_STENCILREF)���� �ٲߴϴ�.
	DEVICE->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

	// disable writes to the depth and black buffers
	// Z���۸� ��Ȱ��ȭ �ؼ� ���̹��ۿ� ����ۿ� ���°� �����Ѵ�.
	// �׸��� blending �� back buffer �� �ٲ��� �ʰ� �Ѵ�.
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, false);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// draw the mirror to the stencil buffer
	DEVICE->SetStreamSource(0, vb, 0, sizeof(TextureVertex));
	DEVICE->SetFVF(TextureVertex::FVF);
	DEVICE->SetMaterial(&mirrorMaterial);
	DEVICE->SetTexture(0, mirrorTex);
	D3DXMATRIX identityMatrix;
	D3DXMatrixIdentity(&identityMatrix);
	DEVICE->SetTransform(D3DTS_WORLD, &identityMatrix);
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 18, 2);

	// re-enable depth write
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, true);

	// only draw reflected teapot to the pixels where the mirror
	// was drawn to.
	// stencil ���� 0x1�� ��쿡�� pass ��
	DEVICE->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	// stencil test�� pass �� stencil buffer ���� ��� ������
	DEVICE->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
	
	// ���ٽ� ���� ���� �ſ￡ �ش��ϴ� �ȼ���
	// 0x1���� ����. �ſ�� �������� �κ��� ǥ��

	// position reflection.
	D3DXMATRIX world, teapotPos, reflection;
	D3DXPLANE plane(0.0f, 0.0f, 1.0f, 0.0f); // xy plane.
	// �������� �ݻ����
	D3DXMatrixReflect(&reflection, &plane);

	D3DXMatrixTranslation
	(
		&teapotPos,
		teapotPosition.x,
		teapotPosition.y,
		teapotPosition.z
	);
	world = teapotPos * reflection;
	
	DEVICE->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	// finally, draw the reflected teapot
	DEVICE->SetTransform(D3DTS_WORLD, &world);
	DEVICE->SetMaterial(&teapotMaterial);
	DEVICE->SetTexture(0, 0);

	// �����ڰ� �ݻ�Ǿ� �޸��� ���̰� �Ǵ�
	// �� ��带 �ݴ���Ѵ�.
	// �� ������ ���ϸ� �ø��Ǿ� ������ �ʴ´�.
	// ��ư �ݻ�� �����ڸ� �������ؾ���
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	teapot->DrawSubset(0);

	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	DEVICE->SetRenderState(D3DRS_STENCILENABLE, false);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
