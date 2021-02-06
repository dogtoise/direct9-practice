#include "stdafx.h"
#include "..\Headers\TexCube.h"
#include "Cube.h"
#include "MaterialHelper.h"

TexCube::TexCube()
{
}


TexCube::~TexCube()
{
}

void TexCube::Setup()
{
	box = new Cube();

	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Specular = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	light.Direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	DEVICE->SetLight(0, &light);
	DEVICE->LightEnable(0, true);

	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);

	D3DXCreateTextureFromFile(
		DEVICE,
		L"../../Resources/crate.jpg",
		&texture);

	// Set Texture Filter States.
	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f, // 90 - degree
		(float)WIN_WIDTH / (float)WIN_HEIGHT,
		1.0f,
		1000.0f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);

}

void TexCube::Cleanup()
{
	delete box;
	texture->Release();
}

void TexCube::Display()
{
	static float angle = (3.0f * D3DX_PI) / 2.0f;
	static float height = 2.0f;

	if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
		angle -= 0.005f;

	if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
		angle += 0.005f;

	if (::GetAsyncKeyState(VK_UP) & 0x8000f)
		height += 0.5f;

	if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
		height -= 0.5f;

	D3DXVECTOR3 position(cosf(angle) * 3.0f, height, sinf(angle) * 3.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);

	DEVICE->SetTransform(D3DTS_VIEW, &viewMatrix);

	DEVICE->SetMaterial(&MaterialHelper::WHITE_MTRL);
	DEVICE->SetTexture(0, texture);

	box->draw(0, 0, 0);

	


}
