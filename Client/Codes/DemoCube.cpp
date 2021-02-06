#include "stdafx.h"
#include "..\Headers\DemoCube.h"
#include "VertexTypes.h"

DemoCube::DemoCube()
{
}


DemoCube::~DemoCube()
{
}

void DemoCube::Setup()
{
	DEVICE->CreateVertexBuffer
	(
		8 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&VB,
		0
	);

	DEVICE->CreateIndexBuffer
	(
		36 * sizeof(WORD),
		D3DUSAGE_WRITEONLY, 
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&IB,
		0
	);

	Vertex* vertices;
	VB->Lock(0, 0, (void**)&vertices, 0);

	// vertices of a unit cube
	vertices[0] = Vertex(-1.0f, -1.0f, -1.0f);
	vertices[1] = Vertex(-1.0f, 1.0f, -1.0f);
	vertices[2] = Vertex(1.0f, 1.0f, -1.0f);
	vertices[3] = Vertex(1.0f, -1.0f, -1.0f);
	vertices[4] = Vertex(-1.0f, -1.0f, 1.0f);
	vertices[5] = Vertex(-1.0f, 1.0f, 1.0f);
	vertices[6] = Vertex(1.0f, 1.0f, 1.0f);
	vertices[7] = Vertex(1.0f, -1.0f, 1.0f);
	
	VB->Unlock();

	// define the triangle of the cube.
	WORD* indices = 0;
	IB->Lock(0, 0, (void**)&indices, 0);

	// front side
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	// back side
	indices[6] = 4; indices[7] = 6; indices[8] = 5;
	indices[9] = 4; indices[10] = 7; indices[11] = 6;

	// left side
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;

	// right side
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;

	// top
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	// bottom
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	IB->Unlock();

	D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
	// what is target? 
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX viewMatrix;

	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);

	DEVICE->SetTransform(D3DTS_VIEW, &viewMatrix);


	// Set the projection matrix
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH
	(
		&proj,
		D3DX_PI* 0.5f,  // 90 degree
		(float)WIN_WIDTH / (float)WIN_HEIGHT,
		1.0f,
		1000.0f
	);

	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);


	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);


}

void DemoCube::Cleanup()
{
	VB->Release();
	IB->Release();
}

void DemoCube::Display()
{
	// spin the cube
	D3DXMATRIX Rx, Ry;

	// rotate 45 degree on x-axis
	D3DXMatrixRotationX(&Rx, 3.14f / 4.0f);

	static float y = 0.0f;
	D3DXMatrixRotationY(&Ry, y);
	y += 0.001f;

	// reset angle to zero when angle reaches 2 * PI
	if (y >= 6.28f)
		y = 0.0f;


	D3DXMATRIX worldMatrix = Rx * Ry;

	DEVICE->SetTransform(D3DTS_WORLD, &worldMatrix);

	DEVICE->SetStreamSource(0, VB, 0, sizeof(Vertex));
	DEVICE->SetIndices(IB);
	DEVICE->SetFVF(Vertex::FVF);

	// Draw cube
	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
}
