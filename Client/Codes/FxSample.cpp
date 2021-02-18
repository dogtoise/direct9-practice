#include "stdafx.h"
#include "..\Headers\FxSample.h"
#include "ShadedCube.h"
FxSample::FxSample()
{
}


FxSample::~FxSample()
{
}

void FxSample::Setup()
{
	HRESULT hr = 0;
	shadedCube = new ShadedCube();

	D3DXCreateTextureFromFile(
		DEVICE,
		L"../../Resources/crate.jpg",
		&texture);

	D3DXCreateEffectFromFile(DEVICE, L"../../Shaders/TestShader.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, nullptr);

	D3DXMatrixPerspectiveFovLH(
		&projMatrix, D3DX_PI * 0.25f,
		(float)WIN_WIDTH / (float)WIN_HEIGHT, 1.0f, 1000.0f);

	D3DXVECTOR3 position(0, 2, -2);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);
}

void FxSample::Cleanup()
{
}

void FxSample::Display()
{
	DEVICE->SetStreamSource(0, shadedCube->_vb, 0, shadedCube->vertexSize);
	DEVICE->SetVertexDeclaration(shadedCube->m_pDeclare);
	DEVICE->SetIndices(shadedCube->_ib);

	D3DXMATRIX yRot;

	static float y = 0.0f;

	D3DXMatrixRotationY(&yRot, y);
	y += 0.001f;

	if (y >= 6.28f)
		y = 0.0f;

	D3DXVECTOR4 diffuse(0, 0, 0, 0);

	m_pEffect->SetValue("WorldMatrix", &yRot, sizeof(yRot));
	m_pEffect->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
	m_pEffect->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));
	m_pEffect->SetValue("Diffuse", &diffuse, sizeof(diffuse));
	//m_pEffect->SetTexture("BaseMap", texture);
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
}
