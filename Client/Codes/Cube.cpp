#include "stdafx.h"
#include "..\Headers\Cube.h"
#include "VertexTypes.h"

Cube::Cube()
{
	DEVICE->CreateVertexBuffer
	(
		24 * sizeof(TextureVertex),
		D3DUSAGE_WRITEONLY,
		TextureVertex::FVF,
		D3DPOOL_MANAGED,
		&_vb,
		0
	);

	TextureVertex* vertices;
	
	_vb->Lock(0, 0, (void**)&vertices, 0);

	// fill in the front face vertex data
	vertices[0] = TextureVertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	vertices[1] = TextureVertex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vertices[2] = TextureVertex(1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	vertices[3] = TextureVertex(1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	// fill in the back face verticesertex data
	vertices[4] = TextureVertex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	vertices[5] = TextureVertex(1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	vertices[6] = TextureVertex(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	vertices[7] = TextureVertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	// fill in the top face verticesertex data
	vertices[8] = TextureVertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	vertices[9] = TextureVertex(-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	vertices[10] = TextureVertex(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	vertices[11] = TextureVertex(1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

	// fill in the bottom face TextureVertex data
	vertices[12] = TextureVertex(-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	vertices[13] = TextureVertex(1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	vertices[14] = TextureVertex(1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	vertices[15] = TextureVertex(-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

	// fill in the left face TextureVertex data
	vertices[16] = TextureVertex(-1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	vertices[17] = TextureVertex(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	vertices[18] = TextureVertex(-1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	vertices[19] = TextureVertex(-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// fill in the right face TextureVertex data
	vertices[20] = TextureVertex(1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	vertices[21] = TextureVertex(1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	vertices[22] = TextureVertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	vertices[23] = TextureVertex(1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	_vb->Unlock();


	DEVICE->CreateIndexBuffer
	(
		36 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_ib,
		0
	);

	WORD* indices = 0;
	_ib->Lock(0, 0, (void**)&indices, 0);

	// findicesll indicesn the front face indicesndex data
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	// findicesll indicesn the back face indicesndex data
	indices[6] = 4; indices[7] = 5; indices[8] = 6;
	indices[9] = 4; indices[10] = 6; indices[11] = 7;

	// findicesll indicesn the top face indicesndex data
	indices[12] = 8; indices[13] = 9; indices[14] = 10;
	indices[15] = 8; indices[16] = 10; indices[17] = 11;

	// findicesll indicesn the bottom face indicesndex data
	indices[18] = 12; indices[19] = 13; indices[20] = 14;
	indices[21] = 12; indices[22] = 14; indices[23] = 15;

	// findicesll indicesn the left face indicesndex data
	indices[24] = 16; indices[25] = 17; indices[26] = 18;
	indices[27] = 16; indices[28] = 18; indices[29] = 19;

	// findicesll indicesn the rindicesght face indicesndex data
	indices[30] = 20; indices[31] = 21; indices[32] = 22;
	indices[33] = 20; indices[34] = 22; indices[35] = 23;

	_ib->Unlock();
}


Cube::~Cube()
{
	if (_vb)
	{
		_vb->Release();
		_vb = nullptr;
	}
	if (_ib)
	{
		_ib->Release();
		_ib = nullptr;
	}
}

bool Cube::draw(D3DXMATRIX * world, D3DMATERIAL9 * mtrl, IDirect3DTexture9 * tex)
{
	if (world)
		DEVICE->SetTransform(D3DTS_WORLD, world);
	if (mtrl)
		DEVICE->SetMaterial(mtrl);
	if (tex)
		DEVICE->SetTexture(0,tex);

	DEVICE->SetStreamSource(0, _vb, 0, sizeof(TextureVertex));
	DEVICE->SetIndices(_ib);
	DEVICE->SetFVF(TextureVertex::FVF);
	DEVICE->DrawIndexedPrimitive
	(
		D3DPT_TRIANGLELIST,
		0, 
		0, 
		24,
		0, 
		12
	);

	return true;
}
