#include "stdafx.h"
#include "..\Headers\LitPyramid.h"
#include "VertexTypes.h"


LitPyramid::LitPyramid()
{
}


LitPyramid::~LitPyramid()
{
}

void LitPyramid::Setup()
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, true);

	// Create the vertex buffer for the pyramid

	DEVICE->CreateVertexBuffer
	(
		12 * sizeof(PyramidVertex),
		D3DUSAGE_WRITEONLY,
		PyramidVertex::FVF,
		D3DPOOL_MANAGED,
		&pyramidBuffer,
		0
	);

	// fill the vertex buffer with pyramid data.

	PyramidVertex * vertices;

	pyramidBuffer->Lock(0, 0, (void**)&vertices, 0);
	// front face
	vertices[0] = PyramidVertex(-1.0f, 0.0f, -1.0f, 0.0f, 0.707f, -0.707f);
	vertices[1] = PyramidVertex(0.0f, 1.0f, 0.0f, 0.0f, 0.707f, -0.707f);
	vertices[2] = PyramidVertex(1.0f, 0.0f, -1.0f, 0.0f, 0.707f, -0.707f);

	// left face
	vertices[3] = PyramidVertex(-1.0f, 0.0f, 1.0f, -0.707f, 0.707f, 0.0f);
	vertices[4] = PyramidVertex(0.0f, 1.0f, 0.0f, -0.707f, 0.707f, 0.0f);
	vertices[5] = PyramidVertex(-1.0f, 0.0f, -1.0f, -0.707f, 0.707f, 0.0f);

	// right face
	vertices[6] = PyramidVertex(1.0f, 0.0f, -1.0f, 0.707f, 0.707f, 0.0f);
	vertices[7] = PyramidVertex(0.0f, 1.0f, 0.0f, 0.707f, 0.707f, 0.0f);
	vertices[8] = PyramidVertex(1.0f, 0.0f, 1.0f, 0.707f, 0.707f, 0.0f);

	// back face
	vertices[9] = PyramidVertex(1.0f, 0.0f, 1.0f, 0.0f, 0.707f, 0.707f);
	vertices[10] = PyramidVertex(0.0f, 1.0f, 0.0f, 0.0f, 0.707f, 0.707f);
	vertices[11] = PyramidVertex(-1.0f, 0.0f, 1.0f, 0.0f, 0.707f, 0.707f);

	pyramidBuffer->Unlock();

	// Create and set the material 

	D3DMATERIAL9 material;
	material.Ambient = WHITE;
	material.Diffuse = WHITE;
	material.Specular = WHITE;
	material.Emissive = BLACK;
	material.Power = 5.0f;

	DEVICE->SetMaterial(&material);

	// setup a directional light

	D3DLIGHT9 dirLight;
	ZeroMemory(&dirLight, sizeof(dirLight));
	dirLight.Type = D3DLIGHT_DIRECTIONAL;
	dirLight.Diffuse = WHITE;
	dirLight.Specular = WHITE * 0.3f;
	dirLight.Ambient = WHITE * 0.6f;
	dirLight.Direction = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	// set and enable the light

	DEVICE->SetLight(0, &dirLight);
	DEVICE->LightEnable(0, true);


	// automatic normalization of vertex normal
	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);


	// Position and aim the camera.
	D3DXVECTOR3 pos(0.0f, 1.0f, -3.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &pos, &target, &up);
	DEVICE->SetTransform(D3DTS_VIEW, &viewMatrix);

	// Set the projection matrix

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f, // 90 - degree
		(float)WIN_WIDTH / (float)WIN_HEIGHT,
		1.0f,
		1000.0f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);
}

void LitPyramid::Cleanup()
{
	pyramidBuffer->Release();
}

void LitPyramid::Display()
{
	D3DXMATRIX yRot;

	static float y = 0.0f;

	D3DXMatrixRotationY(&yRot, y);
	y += 0.001f;

	if (y >= 6.28f)
		y = 0.0f;

	DEVICE->SetTransform(D3DTS_WORLD, &yRot);

	// Draw the scene

	DEVICE->SetStreamSource(0, pyramidBuffer, 0, sizeof(PyramidVertex));
	DEVICE->SetFVF(PyramidVertex::FVF);
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);

	
}
