#include "stdafx.h"
#include "..\Headers\Triangle.h"
#include "CGraphicDevice.h"
#include "VertexTypes.h"

Triangle::Triangle()
{
}


Triangle::~Triangle()
{
}

bool Triangle::Setup()
{
	DEVICE->CreateVertexBuffer
	(
		3 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&triangleBuffer,
		0
	);
	int a = 0;
	Vertex* vertices;
	triangleBuffer->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = Vertex(-1.0f, 0.0f, 2.0f);
	vertices[1] = Vertex(0.0f, 1.0f, 2.0f);
	vertices[2] = Vertex(1.0f, 0.0f, 2.0f);

	triangleBuffer->Unlock();

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH
	(
		&proj,
		D3DX_PI * 0.5f, 
		WIN_WIDTH / WIN_HEIGHT,
		1.0f, 
		1000.0f
	);
	D3DXVECTOR3 vec;
	vec.x = 4;
	vec.y = 10;
	vec.z = -2;
	D3DXMATRIX mat;
	D3DXMatrixTranslation(&mat, vec.x, vec.y, vec.z);

	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);

	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return true;
}

void Triangle::Cleanup()
{
	triangleBuffer->Release();
}

bool Triangle::Display(float timeDelta)
{
	DEVICE->SetStreamSource(0, triangleBuffer, 0, sizeof(Vertex));
	DEVICE->SetFVF(Vertex::FVF);

	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	return true;
}
