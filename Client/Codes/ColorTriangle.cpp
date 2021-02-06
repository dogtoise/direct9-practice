#include "stdafx.h"
#include "..\Headers\ColorTriangle.h"
#include "VertexTypes.h"

ColorTriangle::ColorTriangle()
{
}


ColorTriangle::~ColorTriangle()
{
}

void ColorTriangle::Setup()
{
	DEVICE->CreateVertexBuffer
	(
		3 * sizeof(ColorVertex),
		D3DUSAGE_WRITEONLY,
		ColorVertex::FVF,
		D3DPOOL_MANAGED,
		&triangleBuffer,
		0
	);

	ColorVertex* vertices;
	triangleBuffer->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = ColorVertex(-1.0f, 0.0f, 2.0f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[1] = ColorVertex(0.0f, 1.0f, 2.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[2] = ColorVertex(1.0f, 0.0f, 2.0f, D3DCOLOR_XRGB(0, 0, 255));

	triangleBuffer->Unlock();

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH
	(
		&proj,
		D3DX_PI * 0.5f, // 90 degree
		WIN_WIDTH / WIN_HEIGHT,
		1.0f,
		1000.0f
	);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);


}

void ColorTriangle::Cleanup()
{
	triangleBuffer->Release();
}

void ColorTriangle::Display()
{
	DEVICE->SetFVF(ColorVertex::FVF);
	DEVICE->SetStreamSource(0, triangleBuffer, 0, sizeof(ColorVertex));

	D3DXMatrixTranslation(&WorldMatrix, -1.25, 0.0f, 0.0f);
	DEVICE->SetTransform(D3DTS_WORLD, &WorldMatrix);

	DEVICE->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	D3DXMatrixTranslation(&WorldMatrix, 1.25f, 0.0f, 0.0f);
	DEVICE->SetTransform(D3DTS_WORLD, &WorldMatrix);

	DEVICE->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}
