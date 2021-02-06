#include "stdafx.h"
#include "..\Headers\DirectionalLight.h"
#include "MaterialHelper.h"
#include "LightHelper.h"

DirectionalLight::DirectionalLight()
{
}


DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::Setup()
{
	// create object
	D3DXCreateTeapot(DEVICE, &objects[0], 0);
	D3DXCreateSphere(DEVICE, 1.0f, 20, 20, &objects[1], 0);
	D3DXCreateTorus(DEVICE, 0.5f, 1.0f, 20, 20, &objects[2], 0);
	D3DXCreateCylinder(DEVICE, 0.5f, 0.5f, 2.0f, 20, 20, &objects[3], 0);

	// build world matrices - position the objects  in world space
	D3DXMatrixTranslation(&worldMatrices[0], 0.0f, 2.0f, 0.0f);
	D3DXMatrixTranslation(&worldMatrices[1], 0.0f, -2.0f, 0.0f);
	D3DXMatrixTranslation(&worldMatrices[2], -3.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&worldMatrices[3], 3.0f, 0.0f, 0.0f);

	// setup the object's material
	materials[0] = MaterialHelper::RED_MTRL;
	materials[1] = MaterialHelper::BLUE_MTRL;
	materials[2] = MaterialHelper::GREEN_MTRL;
	materials[3] = MaterialHelper::YELLOW_MTRL;

	// setup a directional light
	D3DXVECTOR3 dir(1.0f, -0.0f, 0.25f);
	D3DXCOLOR color = WHITE;
	D3DLIGHT9 dirLight = LightHelper::InitDirectionalLight(&dir, &color);

	// set and enable the light
	DEVICE->SetLight(0, &dirLight);
	DEVICE->LightEnable(0, true);


	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, false);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.25f, // 45 - degree
		(float)WIN_WIDTH / (float)WIN_HEIGHT,
		1.0f,
		1000.0f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);
}

void DirectionalLight::Cleanup()
{
	for (int i = 0; i < 4; i++)
		objects[i]->Release();
}

void DirectionalLight::Display()
{
	static float angle = (3.0f * D3DX_PI) / 2.0f;
	static float height = 5.0f;

	if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
		angle -= 0.05f;

	if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
		angle += 0.05f;

	if (::GetAsyncKeyState(VK_UP) & 0x8000f)
		height += 0.5f;

	if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
		height -= 0.5f;

	D3DXVECTOR3 position(cosf(angle) * 7.0f, height, sinf(angle) * 7.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX viewMatrix;

	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);

	DEVICE->SetTransform(D3DTS_VIEW, &viewMatrix);


	// draw the scene
	for (int i = 0; i < 4; i++)
	{
		DEVICE->SetMaterial(&materials[i]);
		DEVICE->SetTransform(D3DTS_WORLD, &worldMatrices[i]);
		objects[i]->DrawSubset(0);
	}



}
