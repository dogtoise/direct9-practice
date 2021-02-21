#include "stdafx.h"
#include "..\Headers\DeferredWithLight.h"
#include "ShadedCube.h"
#include "ShadedQuad.h"

DeferredWithLight::DeferredWithLight()
{
}


DeferredWithLight::~DeferredWithLight()
{
}

void DeferredWithLight::Setup()
{
	HRESULT hr = 0;
	leftCube = new ShadedCube();
	rightCube = new ShadedCube();

	resultScreen = new ShadedQuad();

	D3DXCreateTextureFromFile(
		DEVICE,
		L"../../Resources/crate.jpg",
		&cubeTexture);

	D3DXCreateEffectFromFile(DEVICE, L"../../Shaders/DeferredShader.fx", nullptr, nullptr, 0, nullptr, &DeferredShader, nullptr);
	D3DXCreateEffectFromFile(DEVICE, L"../../Shaders/PointLight.fx", nullptr, nullptr, 0, nullptr, &PointLightShader, nullptr);

	D3DXCreateTexture
	(
		DEVICE,
		WIN_WIDTH,
		WIN_HEIGHT,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&depthRTTexture
	);
	depthRTTexture->GetSurfaceLevel(0, &depthRTSurface);

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
		&normalRTTexture
	);
	normalRTTexture->GetSurfaceLevel(0, &normalRTSurface);


	D3DXCreateTexture
	(
		DEVICE,
		WIN_WIDTH,
		WIN_HEIGHT,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&specularRTTextue
	);
	specularRTTextue->GetSurfaceLevel(0, &specularRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WIN_WIDTH,
		WIN_HEIGHT,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&stashRTTexture
	);
	stashRTTexture->GetSurfaceLevel(0, &stashRTSurface);



	D3DLIGHT9 light1;
	light1.Type = D3DLIGHT_POINT;
	light1.Diffuse = D3DXCOLOR(3.0f, 3.0f, 3.0f, 3.0f);
	light1.Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	//light1.Specular = D3DXCOLOR(255, 255, 255, 255);
	light1.Position = D3DXVECTOR3(-7, 0, 7);
	light1.Range = 15;
	light1.Attenuation0 = 0.0f;
	light1.Attenuation1 = 0.2f;
	light1.Attenuation2 = 0.0f;


	D3DLIGHT9 light2;
	light2.Type = D3DLIGHT_POINT;
	light2.Diffuse = D3DXCOLOR(3.0f, 3.0f, 3.0f, 3.0f);
	light2.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	//light2.Specular = D3DXCOLOR(255, 255, 255, 255);
	light2.Position = D3DXVECTOR3(7, 0, 7);
	light2.Range =10;
	light2.Attenuation0 = 0.0f;
	light2.Attenuation1 = 0.2f;
	light2.Attenuation2 = 0.0f;

	//lights.push_back(light1);
	lights.push_back(light2);
	lights.push_back(light2);
	lights.push_back(light2);
	lights.push_back(light2);
}

void DeferredWithLight::Cleanup()
{
}

void DeferredWithLight::Display()
{
	DeferredPipeline();



}

void DeferredWithLight::DeferredPipeline()
{
	SetMRT();
	DEVICE->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);

	DrawCube(leftCube, -10, 0, 10, D3DXVECTOR4(0, 0, 0, 0));

	DrawCube(rightCube, 10, 0, 10, D3DXVECTOR4(5, 0, 0, 5));

	ResumeMRT();
	DrawLight();
}

void DeferredWithLight::SetMRT()
{
	DEVICE->GetRenderTarget(0, &originSurface);
	
	DEVICE->SetRenderTarget(0, depthRTSurface);
	DEVICE->SetRenderTarget(1, albedoRTSurface);
	DEVICE->SetRenderTarget(2, normalRTSurface);
	//DEVICE->SetRenderTarget(3, specularRTSurface);
}

void DeferredWithLight::ResumeMRT()
{
	DEVICE->SetRenderTarget(0, originSurface);
	DEVICE->SetRenderTarget(1, NULL);
	DEVICE->SetRenderTarget(2, NULL);
	//DEVICE->SetRenderTarget(3, NULL);
}

void DeferredWithLight::DrawCube(ShadedCube * cube, float x, float y, float z, D3DXVECTOR4 diffuse)
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
		(float)WIN_WIDTH / (float)WIN_HEIGHT, 5.0f, 100.0f);

	// set view
	D3DXVECTOR3 position(0, 3, -10);
	eyePosition = position;
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);

	// set world
	D3DXMatrixScaling(&worldMatrix, 1, 1, 1);
	D3DXMatrixTranslation(&worldMatrix, x, y, z);


	D3DXVECTOR4 worldPos(x, y, z, 1);

	DeferredShader->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
	DeferredShader->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
	DeferredShader->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));
	DeferredShader->SetValue("Diffuse", &diffuse, sizeof(diffuse));

	DeferredShader->SetValue("WorldPosition", &worldPos, sizeof(worldPos));
	//DEVICE->SetTexture(0, cubeTexture);



	D3DXHANDLE cubeTexHandle = DeferredShader->GetParameterByName(0, "CubeTex");
	DeferredShader->SetTexture(cubeTexHandle, cubeTexture);

	DeferredShader->SetTechnique("GBuffer");
	DeferredShader->Begin(0, 0);
	{
		DeferredShader->BeginPass(0);

		DEVICE->DrawIndexedPrimitive
		(
			D3DPT_TRIANGLELIST,
			0,
			0,
			24,
			0,
			12
		);
		DeferredShader->EndPass();
	}
	DeferredShader->End();
}

void DeferredWithLight::DrawLight()
{

	DEVICE->ColorFill(stashRTSurface, NULL, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));

	for (int i = 0; i < lights.size(); i++)
	{
		D3DXMATRIX worldMatrix;
		D3DXMATRIX viewMatrix;
		D3DXMATRIX projMatrix;

		D3DXMATRIX viewMatrixInv;
		D3DXMATRIX projMatrixInv;

		DEVICE->SetStreamSource(0, resultScreen->_vb, 0, resultScreen->vertexSize);
		DEVICE->SetVertexDeclaration(resultScreen->m_pDeclare);
		DEVICE->SetIndices(resultScreen->_ib);

		D3DXMatrixOrthoLH(&projMatrix, WIN_WIDTH, WIN_HEIGHT, 0, 1000);
		D3DXMatrixScaling(&worldMatrix, WIN_WIDTH, WIN_HEIGHT, 1);
		D3DXMatrixIdentity(&viewMatrix);
		

		PointLightShader->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
		PointLightShader->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
		PointLightShader->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));
	

		// set projection
		D3DXMatrixPerspectiveFovLH(
			&projMatrix, D3DX_PI * 0.25f,
			(float)WIN_WIDTH / (float)WIN_HEIGHT, 5.0f, 100.0f);

		// set view
		D3DXVECTOR3 position(0, 3, -10);
		eyePosition = position;
		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
		D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);
		D3DXMatrixInverse(&viewMatrixInv, NULL, &viewMatrix);
		D3DXMatrixInverse(&projMatrixInv, NULL, &projMatrix);

		PointLightShader->SetValue("TempViewMatrix", &viewMatrix, sizeof(viewMatrix));
		PointLightShader->SetValue("TempProjMatrix", &projMatrix, sizeof(projMatrix));
		PointLightShader->SetValue("ViewMatrixInv", &viewMatrixInv, sizeof(viewMatrixInv));
		PointLightShader->SetValue("ProjMatrixInv", &projMatrixInv, sizeof(projMatrixInv));


		D3DXHANDLE depthMap = PointLightShader->GetParameterByName(0, "DepthTex");
		PointLightShader->SetTexture(depthMap, depthRTTexture);

		D3DXHANDLE albedoMap = PointLightShader->GetParameterByName(0, "AlbedoTex");
		PointLightShader->SetTexture(albedoMap, albedoRTTexture);

		D3DXHANDLE normalMap = PointLightShader->GetParameterByName(0, "NormalTex");
		PointLightShader->SetTexture(normalMap, normalRTTexture);

		D3DXHANDLE stashMap = PointLightShader->GetParameterByName(0, "StashTex");
		PointLightShader->SetTexture(stashMap, stashRTTexture);

		//D3DXHANDLE specularMap = PointLightShader->GetParameterByName(0, "SpecularTex");
		//PointLightShader->SetTexture(specularMap, specularRTTextue);


		PointLightShader->SetValue("EyePosition", &eyePosition , sizeof(eyePosition));
		PointLightShader->SetValue("LightPosition", &lights[i].Position, sizeof(lights[i].Position));
		PointLightShader->SetValue("LightDiffuse", &lights[i].Diffuse, sizeof(lights[i].Diffuse));
		PointLightShader->SetValue("LightAmbient", &lights[i].Ambient, sizeof(lights[i].Ambient));
		PointLightShader->SetValue("LightRange", &lights[i].Range, sizeof(lights[i].Range));
		PointLightShader->SetValue("LightConstant", &lights[i].Attenuation0, sizeof(lights[i].Attenuation0));
		PointLightShader->SetValue("LightLinear", &lights[i].Attenuation1, sizeof(lights[i].Attenuation1));
		PointLightShader->SetValue("LightExp", &lights[i].Attenuation2, sizeof(lights[i].Attenuation2));


		PointLightShader->SetTechnique("PointLight");
		PointLightShader->Begin(0, 0);
		{
			PointLightShader->BeginPass(0);
			DEVICE->DrawIndexedPrimitive
			(
				D3DPT_TRIANGLELIST,
				0,
				0,
				4,
				0,
				2
			);
			PointLightShader->EndPass();

		}
		PointLightShader->End();
		DEVICE->StretchRect(originSurface, NULL, stashRTSurface, NULL, D3DTEXF_NONE);

	}
}

void DeferredWithLight::DrawResult()
{
}
