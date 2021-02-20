#include "stdafx.h"
#include "..\Headers\RTTSample.h"
#include  "ShadedCube.h"
#include "ShadedQuad.h"

RTTSample::RTTSample()
{
}


RTTSample::~RTTSample()
{
}

void RTTSample::Setup()
{
	HRESULT hr = 0;
	shadedCube = new ShadedCube();
	shadedQuad = new ShadedQuad();

	D3DXCreateTextureFromFile(
		DEVICE,
		L"../../Resources/crate.jpg",
		&texture);
	D3DXCreateEffectFromFile(DEVICE, L"../../Shaders/MultiRender.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, nullptr);

	D3DXMatrixPerspectiveFovLH(
		&projMatrix, D3DX_PI * 0.25f,
		(float)WIN_WIDTH / (float)WIN_HEIGHT, 1.0f, 1000.0f);

	D3DXVECTOR3 position(0, 0, -10);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);

	/*DEVICE->CreateTexture(WIN_WIDTH, WIN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		texFormat,
		D3DPOOL_DEFAULT,
		&defaultRTTexture,
		NULL
	);*/
	D3DXCreateTexture
	(
		DEVICE,
		WIN_WIDTH,
		WIN_HEIGHT,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&defaultRTTexture
	);
	defaultRTTexture->GetSurfaceLevel(0, &defaultRTSurface);


}

void RTTSample::Cleanup()
{
}

void RTTSample::Display()
{
	IDirect3DSurface9 * pOldRT;
	DEVICE->GetRenderTarget(0, &pOldRT);

	DEVICE->SetRenderTarget(0, defaultRTSurface);
	//DEVICE->Clear(0, nullptr, D3DCLEAR_TARGET, D3DXCOLOR(255, 0, 0, 255), 1.0f, 0);
	DEVICE->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);
	//DEVICE->BeginScene();
	//DEVICE->BeginScene();



	DEVICE->SetStreamSource(0, shadedCube->_vb, 0, shadedCube->vertexSize);
	DEVICE->SetVertexDeclaration(shadedCube->m_pDeclare);
	DEVICE->SetIndices(shadedCube->_ib);


	D3DXMatrixPerspectiveFovLH(
		&projMatrix, D3DX_PI * 0.25f,
		(float)WIN_WIDTH / (float)WIN_HEIGHT, 1.0f, 1000.0f);


	D3DXMATRIX yRot;

	static float y = 0.0f;
	D3DXVECTOR3 position(0, 3, -10);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);

	D3DXMatrixRotationY(&yRot, y);
	y += 0.001f;

	if (y >= 6.28f)
		y = 0.0f;
	D3DXVECTOR4 diffuse(0, 0, 0, 0);
	m_pEffect->SetValue("WorldMatrix", &yRot, sizeof(yRot));
	m_pEffect->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
	m_pEffect->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));
	m_pEffect->SetValue("Diffuse", &diffuse, sizeof(diffuse));
	DEVICE->SetTexture(0, texture);


	m_pEffect->SetTechnique("Default_Technique");
	m_pEffect->Begin(0, 0);
	{
		m_pEffect->BeginPass(0);

		DEVICE->DrawIndexedPrimitive
		(
			D3DPT_TRIANGLELIST,
			0,
			0,
			24,
			0,
			12
		);

		m_pEffect->EndPass();


	}
	m_pEffect->End();

	//DEVICE->EndScene();
	//DEVICE->EndScene();


	//DEVICE->GetRenderTarget(0, &defaultRTSurface);
	//DEVICE->GetRenderTarget(0, &defaultRTSurface);
	//DEVICE->SetRenderTarget(0, NULL);
	DEVICE->SetRenderTarget(0, pOldRT);

	//DEVICE->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);
	//DEVICE->BeginScene();


	DEVICE->SetStreamSource(0, shadedQuad->_vb, 0, shadedQuad->vertexSize);
	DEVICE->SetVertexDeclaration(shadedQuad->m_pDeclare);
	DEVICE->SetIndices(shadedQuad->_ib);
	D3DXMatrixOrthoLH(&projMatrix, WIN_WIDTH, WIN_HEIGHT, 0, 1000);
	D3DXMatrixScaling(&worldMatrix, WIN_WIDTH, WIN_HEIGHT, 1);
	D3DXMatrixIdentity(&viewMatrix);

	m_pEffect->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
	m_pEffect->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
	m_pEffect->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));
	m_pEffect->SetValue("Diffuse", &diffuse, sizeof(diffuse));
	//m_pEffect->SetTexture("BaseMap", texture);
	DEVICE->SetTexture(0, defaultRTTexture);
	
	m_pEffect->SetTechnique("Merge_Technique");
	m_pEffect->Begin(0, 0);
	{
		m_pEffect->BeginPass(0);

		DEVICE->DrawIndexedPrimitive
		(
			D3DPT_TRIANGLELIST,
			0,
			0,
			4,
			0,
			2
		);
		m_pEffect->EndPass();

	}
	m_pEffect->End();
	//DEVICE->EndScene();

	//DEVICE->EndScene();


}
