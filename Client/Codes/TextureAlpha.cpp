#include "stdafx.h"
#include "..\Headers\TextureAlpha.h"
#include "VertexTypes.h"
#include "Cube.h"

TextureAlpha::TextureAlpha()
{
}


TextureAlpha::~TextureAlpha()
{
}

void TextureAlpha::Setup()
{
	DEVICE->CreateVertexBuffer
	(
		6 * sizeof(TextureVertex),
		D3DUSAGE_WRITEONLY,
		TextureVertex::FVF,
		D3DPOOL_MANAGED,
		&backDropVB,
		0
	);

	TextureVertex* vertices;
	backDropVB->Lock(0, 0, (void**)&vertices, 0);

	// quad built from two triangles, note texture coordinates:
	vertices[0] = TextureVertex(-10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vertices[1] = TextureVertex(-10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	vertices[2] = TextureVertex(10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	vertices[3] = TextureVertex(-10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vertices[4] = TextureVertex(10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	vertices[5] = TextureVertex(10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	backDropVB->Unlock();

	box = new Cube();

	D3DXCreateTextureFromFile(
		DEVICE,
		L"../../Resources/cratewalpha.dds",
		&crateTex);

	D3DXCreateTextureFromFile(
		DEVICE,
		L"../../Resources/lobbyxpos.jpg",
		&backDropTexture);

	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);


	// use alpha channel in texture for alpha
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	// set blending factors so that alpha component determines transparency
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// disasble lighting 
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);

	D3DXVECTOR3 pos(0.0f, 0.f, -2.5f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH
	(
		&viewMatrix,
		&pos,
		&target,
		&up
	);

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

void TextureAlpha::Cleanup()
{
	crateTex->Release();
	delete box;

	backDropVB->Release();
	backDropTexture->Release();
}

void TextureAlpha::Display()
{
	D3DXMATRIX xRot;
	D3DXMatrixRotationX(&xRot, D3DX_PI * 0.2f);

	static float y = 0.0f;
	D3DXMATRIX yRot;
	D3DXMatrixRotationY(&yRot, y);
	y += 0.005f;
	if (y >= 6.28f)
		y = 0.0f;

	boxWorldMatrix = xRot * yRot;

	// draw back drop
	D3DXMATRIX identityMatrix;
	D3DXMatrixIdentity(&identityMatrix);
	DEVICE->SetStreamSource(0, backDropVB, 0, sizeof(TextureVertex));
	DEVICE->SetFVF(TextureVertex::FVF);
	DEVICE->SetTexture(0, backDropTexture);
	DEVICE->SetTransform(D3DTS_WORLD, &identityMatrix);
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	// draw cube
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	if (box)
		box->draw(&boxWorldMatrix, 0, crateTex);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);


}
