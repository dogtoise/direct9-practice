#include "stdafx.h"
#include "..\Headers\TexQuad.h"
#include "VertexTypes.h"

TexQuad::TexQuad()
{
}


TexQuad::~TexQuad()
{
	

}

void TexQuad::Setup()
{
	DEVICE->CreateVertexBuffer
	(
		6 * sizeof(TextureVertex),
		D3DUSAGE_WRITEONLY,
		TextureVertex::FVF,
		D3DPOOL_MANAGED,
		&quadBuffer,
		0
	);

	TextureVertex * vertices;
	quadBuffer->Lock(0, 0, (void**)&vertices, 0);

	// quad built from two triangles, note texture coordinates:
	vertices[0] = TextureVertex(-1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vertices[1] = TextureVertex(-1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	vertices[2] = TextureVertex(1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	vertices[3] = TextureVertex(-1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vertices[4] = TextureVertex(1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	vertices[5] = TextureVertex(1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	quadBuffer->Unlock();


	D3DXCreateTextureFromFile(DEVICE,
		L"../../Resources/dx5_logo.bmp",
		&texture);
	if (texture == nullptr)
		assert(false);
	DEVICE->SetTexture(0, texture);

	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// don't use lighting for this sample.

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);

	// set the projection matrix

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f, // 90 - degree
		(float)WIN_WIDTH / (float)WIN_HEIGHT,
		1.0f,
		1000.0f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);

}

void TexQuad::Cleanup()
{
	quadBuffer->Release();
	texture->Release();
}

void TexQuad::Display()
{
	DEVICE->SetStreamSource(0, quadBuffer, 0, sizeof(TextureVertex));
	DEVICE->SetFVF(TextureVertex::FVF);
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);


}
