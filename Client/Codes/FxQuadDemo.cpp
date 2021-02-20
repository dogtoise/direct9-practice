#include "stdafx.h"
#include "..\Headers\FxQuadDemo.h"
#include "ShadedQuad.h"


FxQuadDemo::FxQuadDemo()
{
}


FxQuadDemo::~FxQuadDemo()
{
}

void FxQuadDemo::Setup()
{
	HRESULT hr = 0;
	shadedQuad = new ShadedQuad();

	D3DXCreateTextureFromFile(
		DEVICE,
		L"../../Resources/crate.jpg",
		&texture);

	D3DXCreateEffectFromFile(DEVICE, L"../../Shaders/TestShader.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, nullptr);

	D3DXMatrixPerspectiveFovLH(
		&projMatrix, D3DX_PI * 0.25f,
		(float)WIN_WIDTH / (float)WIN_HEIGHT, 0.0f, 1000.0f);
	D3DXMatrixOrthoLH(&projMatrix, WIN_WIDTH, WIN_HEIGHT, 0, 1000);

	D3DXVECTOR3 position(0, 2, -2);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);



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

void FxQuadDemo::Cleanup()
{
}

void FxQuadDemo::Display()
{
	IDirect3DSurface9* pOldSurf;
	DEVICE->GetRenderTarget(0, &pOldSurf);

	DEVICE->SetRenderTarget(0, defaultRTSurface);

	DEVICE->SetStreamSource(0, shadedQuad->_vb, 0, shadedQuad->vertexSize);
	DEVICE->SetVertexDeclaration(shadedQuad->m_pDeclare);
	DEVICE->SetIndices(shadedQuad->_ib);

	D3DXMatrixScaling(&worldMatrix, WIN_WIDTH, WIN_HEIGHT, 1);
	

	D3DXMatrixIdentity(&viewMatrix);
	D3DXVECTOR4 diffuse(0, 0, 0, 0);
	m_pEffect->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
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
			4,
			0,
			2
		);
		m_pEffect->EndPass();

	}
	m_pEffect->End();








	DEVICE->SetRenderTarget(0, pOldSurf);


	DEVICE->SetStreamSource(0, shadedQuad->_vb, 0, shadedQuad->vertexSize);
	DEVICE->SetVertexDeclaration(shadedQuad->m_pDeclare);
	DEVICE->SetIndices(shadedQuad->_ib);

	D3DXMatrixScaling(&worldMatrix, WIN_WIDTH, WIN_HEIGHT, 1);


	D3DXMatrixIdentity(&viewMatrix);
	m_pEffect->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
	m_pEffect->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
	m_pEffect->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));
	m_pEffect->SetValue("Diffuse", &diffuse, sizeof(diffuse));

	DEVICE->SetTexture(0, defaultRTTexture);

	m_pEffect->SetTechnique("Default_Technique");
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


}
