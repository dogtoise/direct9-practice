#include "stdafx.h"
#include "..\Headers\SimpleDeferred.h"
#include "ShadedCube.h"
#include "ShadedQuad.h"


SimpleDeferred::SimpleDeferred()
{
}


SimpleDeferred::~SimpleDeferred()
{
}

void SimpleDeferred::Setup()
{
	HRESULT hr = 0;

	leftCube = new ShadedCube();
	rightCube = new ShadedCube();

	resultScreen = new ShadedQuad();
	D3DXCreateTextureFromFile(
		DEVICE,
		L"../../Resources/crate.jpg",
		&cubeTexture);

	D3DXCreateEffectFromFile(DEVICE, L"../../Shaders/SimpleDeferred.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, nullptr);


	D3DXCreateTexture
	(
		DEVICE,
		WIN_WIDTH,
		WIN_HEIGHT,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&positionRTTexture
	);
	positionRTTexture->GetSurfaceLevel(0, &positionRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WIN_WIDTH,
		WIN_HEIGHT,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&albedoRTTexture
	);
	albedoRTTexture->GetSurfaceLevel(0, &albedoRTSurface);


	D3DXCreateTexture
	(
		DEVICE,
		WIN_WIDTH,
		WIN_HEIGHT,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&diffuseRTTexture
	);
	diffuseRTTexture->GetSurfaceLevel(0, &diffuseRTSurface);


}

void SimpleDeferred::Cleanup()
{
}

void SimpleDeferred::Display()
{
	DeferredPipeline();
}

void SimpleDeferred::DeferredPipeline()
{
	SetMRT();
	DEVICE->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);
	
	DrawCube(leftCube, -10, 0, 10, D3DXVECTOR4(0, 0, 0, 0));

	DrawCube(rightCube, 10, 0, 10, D3DXVECTOR4(5, 0, 0, 5));

	ResumeMRT();

	DrawResult();
}

void SimpleDeferred::SetMRT()
{
	DEVICE->GetRenderTarget(0, &originSurface);

	DEVICE->SetRenderTarget(0, positionRTSurface);
	DEVICE->SetRenderTarget(1, albedoRTSurface);
	DEVICE->SetRenderTarget(2, diffuseRTSurface);

}

void SimpleDeferred::ResumeMRT()
{
	DEVICE->SetRenderTarget(0, originSurface);
	DEVICE->SetRenderTarget(1, NULL);
	DEVICE->SetRenderTarget(2, NULL);
}

void SimpleDeferred::DrawCube(ShadedCube * cube, float x, float y, float z, D3DXVECTOR4 diffuse)
{
	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	DEVICE->SetStreamSource(0, cube->_vb, 0, cube->vertexSize);
	DEVICE->SetVertexDeclaration(cube->m_pDeclare);
	DEVICE->SetIndices(cube->_ib);

	// set projection
	D3DXMatrixPerspectiveFovLH(
		&projMatrix, D3DX_PI * 0.25f,
		(float)WIN_WIDTH / (float)WIN_HEIGHT, 1.0f, 1000.0f);

	// set view
	D3DXVECTOR3 position(0, 3, -10);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);

	// set world
	D3DXMatrixScaling(&worldMatrix, 1, 1, 1);
	D3DXMatrixTranslation(&worldMatrix, x, y, z);

	m_pEffect->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
	m_pEffect->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
	m_pEffect->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));
	m_pEffect->SetValue("Diffuse", &diffuse, sizeof(diffuse));
	//DEVICE->SetTexture(0, cubeTexture);

	D3DXHANDLE cubeTexHandle = m_pEffect->GetParameterByName(0, "CubeTex");
	m_pEffect->SetTexture(cubeTexHandle, cubeTexture);
	
	m_pEffect->SetTechnique("GBuffer");
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

}

void SimpleDeferred::DrawResult()
{
	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	DEVICE->SetStreamSource(0, resultScreen->_vb, 0, resultScreen->vertexSize);
	DEVICE->SetVertexDeclaration(resultScreen->m_pDeclare);
	DEVICE->SetIndices(resultScreen->_ib);

	D3DXMatrixOrthoLH(&projMatrix, WIN_WIDTH, WIN_HEIGHT, 0, 1000);
	D3DXMatrixScaling(&worldMatrix, WIN_WIDTH, WIN_HEIGHT, 1);
	D3DXMatrixIdentity(&viewMatrix);

	m_pEffect->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
	m_pEffect->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
	m_pEffect->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));
	
	D3DXHANDLE positionMap = m_pEffect->GetParameterByName(0, "PositionTex");
	m_pEffect->SetTexture(positionMap, positionRTTexture);

	D3DXHANDLE albedoMap = m_pEffect->GetParameterByName(0, "AlbedoTex");
	m_pEffect->SetTexture(albedoMap, albedoRTTexture);

	D3DXHANDLE diffuseMap = m_pEffect->GetParameterByName(0, "DiffuseTex");
	m_pEffect->SetTexture(diffuseMap, diffuseRTTexture);

	m_pEffect->SetTechnique("OutScreen");
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
