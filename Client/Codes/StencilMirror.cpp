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

	// stencil 버퍼를 켭니다.
	DEVICE->SetRenderState(D3DRS_STENCILENABLE, true);
	// Stencil 쓰기가 항상 성공하도록 합니다.
	// 쓰기가 성공할 경우 stencil에 0x1을 쓰도록 합니다.
	DEVICE->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	DEVICE->SetRenderState(D3DRS_STENCILREF, 0x1);
	DEVICE->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	DEVICE->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
	// depth test가 실패하면 pixel이 가려졌음을 의미함 렌더링할 필요 없음
	DEVICE->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	DEVICE->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	// depth/stencil test가 성공하면 stencil 참조 값을 0x1로 함.
	// D3DSTENCILOP_REPLACE -> 스텐실버퍼 항목을 참조값(D3DRS_STENCILREF)으로 바꿉니다.
	DEVICE->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

	// disable writes to the depth and black buffers
	// Z버퍼를 비활성화 해서 깊이버퍼와 백버퍼에 쓰는걸 방지한다.
	// 그리고 blending 시 back buffer 가 바뀌지 않게 한다.
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
	// stencil 값이 0x1인 경우에만 pass 함
	DEVICE->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	// stencil test가 pass 면 stencil buffer 값을 계속 유지함
	DEVICE->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
	
	// 스텐실 버퍼 내에 거울에 해당하는 픽셀은
	// 0x1값을 가짐. 거울로 렌더링될 부분을 표시

	// position reflection.
	D3DXMATRIX world, teapotPos, reflection;
	D3DXPLANE plane(0.0f, 0.0f, 1.0f, 0.0f); // xy plane.
	// 주전자의 반사행렬
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

	// 주전자가 반사되어 뒷면이 보이게 되니
	// 컬 모드를 반대로한다.
	// 이 설정을 안하면 컬링되어 보이지 않는다.
	// 암튼 반사된 주전자를 렌더링해야함
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	teapot->DrawSubset(0);

	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	DEVICE->SetRenderState(D3DRS_STENCILENABLE, false);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
