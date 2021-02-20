#include "stdafx.h"
#include "MultiTextureRender.h"
#include "ShadedCube.h"
#include "ShadedQuad.h"

MultiTextureRender::MultiTextureRender()
{
}

MultiTextureRender::~MultiTextureRender()
{
}

void MultiTextureRender::Setup()
{
	HRESULT hr = 0;
	shadedCubeA = new ShadedCube();
	shadedCubeB = new ShadedCube();
	shadedQuad = new ShadedQuad();

	D3DXCreateTextureFromFile(
		DEVICE,
		L"../../Resources/crate.jpg",
		&texture);
	D3DXCreateEffectFromFile(DEVICE, L"../../Shaders/MultiRender.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, nullptr);

	D3DXMatrixPerspectiveFovLH(
		&projMatrix, D3DX_PI * 0.25f,
		(float)WIN_WIDTH / (float)WIN_HEIGHT, 1.0f, 1000.0f);

	D3DXVECTOR3 position(0, 2, -2);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);

	DEVICE->CreateTexture(WIN_WIDTH, WIN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		texFormat,
		D3DPOOL_DEFAULT,
		&defaultRTTexture,
		NULL
	);
	defaultRTTexture->GetSurfaceLevel(0, &defaultRTSurface);
	DEVICE->CreateTexture(WIN_WIDTH, WIN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		texFormat,
		D3DPOOL_DEFAULT,
		&alphaRTTexture,
		NULL
	);
	alphaRTTexture->GetSurfaceLevel(0, &alphaRTSurface);
	DEVICE->CreateTexture(WIN_WIDTH, WIN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		texFormat,
		D3DPOOL_DEFAULT,
		&resultRTTexture,
		NULL
	);
	resultRTTexture->GetSurfaceLevel(0, &resultRTSurface);

}

void MultiTextureRender::Cleanup()
{
}

void MultiTextureRender::Display()
{
	IDirect3DSurface9* pOldRT;
	DEVICE->GetRenderTarget(0, &pOldRT);

	DEVICE->SetRenderTarget(0, defaultRTSurface);
	DEVICE->Clear(0, nullptr, D3DCLEAR_TARGET, D3DXCOLOR(255, 0, 0, 255), 1.0f, 0);

	m_pEffect->SetTechnique("Default_Technique");
	m_pEffect->Begin(0, 0);
	{
		m_pEffect->BeginPass(0);
		
		DEVICE->SetStreamSource(0, shadedCubeA->_vb, 0, shadedCubeA->vertexSize);
		DEVICE->SetVertexDeclaration(shadedCubeA->m_pDeclare);
		DEVICE->SetIndices(shadedCubeA->_ib);

		D3DXMATRIX yRot;

		static float y = 0.0f;

		D3DXMatrixRotationY(&yRot, y);
		y += 0.001f;

		if (y >= 6.28f)
			y = 0.0f;

		D3DXVECTOR4 diffuse(0, 0, 0, 0);

		D3DXMatrixTranslation(&yRot, -10, 0, 5);
		m_pEffect->SetValue("WorldMatrix", &yRot, sizeof(yRot));
		m_pEffect->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
		m_pEffect->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));
		m_pEffect->SetValue("Diffuse", &diffuse, sizeof(diffuse));
		DEVICE->SetTexture(0, texture);
		m_pEffect->SetTechnique("Default_Technique");

		m_pEffect->CommitChanges();

		DEVICE->DrawIndexedPrimitive
		(
			D3DPT_TRIANGLELIST,
			0,
			0,
			24,
			0,
			12
		);

		DEVICE->SetStreamSource(0, shadedCubeB->_vb, 0, shadedCubeB->vertexSize);
		DEVICE->SetVertexDeclaration(shadedCubeB->m_pDeclare);
		DEVICE->SetIndices(shadedCubeB->_ib);
		
		D3DXMatrixTranslation(&yRot, 10, 0, 5);
		m_pEffect->SetValue("WorldMatrix", &yRot, sizeof(yRot));
		m_pEffect->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
		m_pEffect->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));
		m_pEffect->SetValue("Diffuse", &diffuse, sizeof(diffuse));
		DEVICE->SetTexture(0, texture);

		m_pEffect->CommitChanges();

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

	DEVICE->SetRenderTarget(0, alphaRTSurface);
	DEVICE->Clear(0, nullptr, D3DCLEAR_TARGET, D3DXCOLOR(0, 0, 0, 0), 1.0f, 0);
	
	m_pEffect->SetTechnique("Alpha_Technique");
	m_pEffect->Begin(0, 0);
	{
		m_pEffect->BeginPass(0);

		DEVICE->SetStreamSource(0, shadedCubeA->_vb, 0, shadedCubeA->vertexSize);
		DEVICE->SetVertexDeclaration(shadedCubeA->m_pDeclare);
		DEVICE->SetIndices(shadedCubeA->_ib);

		D3DXMATRIX yRot;

		static float y = 0.0f;

		D3DXMatrixRotationY(&yRot, y);
		D3DXMatrixTranslation(&yRot, -40, 0, 20);
		y += 0.001f;

		if (y >= 6.28f)
			y = 0.0f;

		D3DXVECTOR4 diffuse(0, 0, 0, 0);

		m_pEffect->SetValue("WorldMatrix", &yRot, sizeof(yRot));
		m_pEffect->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
		m_pEffect->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));
		m_pEffect->SetValue("Diffuse", &diffuse, sizeof(diffuse));
		DEVICE->SetTexture(0, texture);

		m_pEffect->CommitChanges();

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


	DEVICE->SetRenderTarget(0, pOldRT);

	m_pEffect->SetTechnique("Merge_Technique");
	m_pEffect->Begin(0, 0);
	{
		m_pEffect->BeginPass(0);
		DEVICE->SetStreamSource(0, shadedQuad->_vb, 0, shadedQuad->vertexSize);
		DEVICE->SetVertexDeclaration(shadedQuad->m_pDeclare);
		DEVICE->SetIndices(shadedQuad->_ib);


		D3DXMATRIX worldMat;
		D3DXMatrixTranslation(&worldMat, 0, 0, 0);
		D3DXMatrixScaling(&worldMat, 1, 1, 1);

		m_pEffect->SetValue("WorldMatrix", &worldMat, sizeof(worldMat));
		m_pEffect->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
		m_pEffect->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));
		DEVICE->SetTexture(1, defaultRTTexture);
		DEVICE->SetTexture(2, alphaRTTexture);

		m_pEffect->CommitChanges();

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
