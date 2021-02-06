#include "stdafx.h"
#include "..\Headers\Teapot.h"


Teapot::Teapot()
{
}


Teapot::~Teapot()
{
}

void Teapot::Setup()
{
	D3DXCreateTeapot(DEVICE, &teapotMesh, 0);


	D3DXVECTOR3 position(0.0f, 0.0f, -3.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX viewMatrix;

	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);
	DEVICE->SetTransform(D3DTS_VIEW, &viewMatrix);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH
	(
		&proj,
		D3DX_PI * 0.5f , // 90 degree
		WIN_WIDTH / WIN_HEIGHT,
		1.0f, 
		1000.0f
	);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);

	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

void Teapot::Cleanup()
{
	teapotMesh->Release();
}

void Teapot::Display()
{
	// Draw teapot using DrawSubset method with 0 as the argument 
	teapotMesh->DrawSubset(0);

}
