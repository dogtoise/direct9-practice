#include "stdafx.h"
#include "..\Headers\DeferredWithBlur.h"
#include "ShadedQuad.h"
#include "ShadedCube.h"
#include <ctime>

#define BOXCOUNT 10
DeferredWithBlur::DeferredWithBlur()
{
}


DeferredWithBlur::~DeferredWithBlur()
{
}

void DeferredWithBlur::Setup()
{
	std::srand(time(nullptr));

	HRESULT hr = 0;
	for (int i = 0; i < BOXCOUNT; i++)
	{
		cubes.emplace_back(new ShadedCube());
		randomPos.push_back( D3DXVECTOR3(rand() % 20 - 10, rand() % 20 - 10, rand() % 10 + 10));
	}

	lightScreen = new ShadedQuad();
	blurScreen = new ShadedQuad();

	D3DXCreateTextureFromFile(
		DEVICE,
		L"../../Resources/crate.jpg",
		&cubeTexture);

	D3DXCreateEffectFromFile(DEVICE, L"../../Shaders/DeferredShader.fx", nullptr, nullptr, 0, nullptr, &DeferredShader, nullptr);
	D3DXCreateEffectFromFile(DEVICE, L"../../Shaders/PointLight.fx", nullptr, nullptr, 0, nullptr, &PointLightShader, nullptr);
	D3DXCreateEffectFromFile(DEVICE, L"../../Shaders/AmbientLight.fx", nullptr, nullptr, 0, nullptr, &AmbientLightShader, nullptr);
	D3DXCreateEffectFromFile(DEVICE, L"../../Shaders/DirectionalLight.fx", nullptr, nullptr, 0, nullptr, &DirectionalLightShader, nullptr);
	D3DXCreateEffectFromFile(DEVICE, L"../../Shaders/SimpleBlur.fx", nullptr, nullptr, 0, nullptr, &BlurShader, nullptr);


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
		&blurMaskRTTexture
	);
	blurMaskRTTexture->GetSurfaceLevel(0, &blurMaskRTSurface);

	D3DXCreateTexture
	(
		DEVICE,
		WIN_WIDTH,
		WIN_HEIGHT,
		D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&lightRTTexture
	);
	lightRTTexture->GetSurfaceLevel(0, &lightRTSurface);


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
	light1.Position = D3DXVECTOR3(-7, 6, 7);
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
	light2.Range = 10;
	light2.Attenuation0 = 0.0f;
	light2.Attenuation1 = 0.2f;
	light2.Attenuation2 = 0.0f;

	D3DLIGHT9 light3;
	light3.Type = D3DLIGHT_DIRECTIONAL;
	light3.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light3.Direction = D3DXVECTOR3(7, -7, 0);
	light3.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	
	lights.push_back(light1);
	lights.push_back(light2);
//	lights.push_back(light3);
}

void DeferredWithBlur::Cleanup()
{
}

void DeferredWithBlur::Display()
{
	DeferredPipeline();
}

void DeferredWithBlur::DeferredPipeline()
{
	SetGBufferMRT();
	DEVICE->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);

	for (int i = 0; i < BOXCOUNT; i++)
	{
		//D3DXVECTOR3 randPos(rand() % 20 - 10, rand() % 20 - 10, rand() % 10 + 10);
		bool isBlur = i / 2 == 0;
		if (isBlur)
			DrawBlurCube(cubes[i], randomPos[i].x, randomPos[i].y, randomPos[i].z, D3DXVECTOR4(0, 0, 0, 0));
		else
			DrawCube(cubes[i], randomPos[i].x, randomPos[i].y, randomPos[i].z, D3DXVECTOR4(0, 0, 0, 0));
	}

	SetLightMRT();
	//SetOriginMRT();
	DEVICE->ColorFill(stashRTSurface, NULL, D3DXCOLOR(0.f, 0.f, 0.f, 0.f));
	DrawAmbient();
	DrawLight();

	SetOriginMRT();
	DEVICE->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 255), 1.f, 0);

	DrawBlur();
}

void DeferredWithBlur::SetGBufferMRT()
{
	DEVICE->GetRenderTarget(0, &originSurface);

	DEVICE->SetRenderTarget(0, depthRTSurface);
	DEVICE->SetRenderTarget(1, albedoRTSurface);
	DEVICE->SetRenderTarget(2, normalRTSurface);
	DEVICE->SetRenderTarget(3, blurMaskRTSurface);
}

void DeferredWithBlur::SetLightMRT()
{
	DEVICE->SetRenderTarget(0, lightRTSurface);
	DEVICE->SetRenderTarget(1, NULL);
	DEVICE->SetRenderTarget(2, NULL);
	DEVICE->SetRenderTarget(3, NULL);
}

void DeferredWithBlur::SetOriginMRT()
{
	DEVICE->SetRenderTarget(0, originSurface);
	DEVICE->SetRenderTarget(1, NULL);
	DEVICE->SetRenderTarget(2, NULL);
	DEVICE->SetRenderTarget(3, NULL);
}



void DeferredWithBlur::DrawCube(ShadedCube * cube, float x, float y, float z, D3DXVECTOR4 diffuse)
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
	//eyePosition = position;
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

void DeferredWithBlur::DrawBlurCube(ShadedCube * cube, float x, float y, float z, D3DXVECTOR4 diffuse)
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
	//eyePosition = position;
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

	DeferredShader->SetTechnique("GBufferWithBlur");
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

void DeferredWithBlur::DrawAmbient()
{
	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	D3DXMATRIX viewMatrixInv;
	D3DXMATRIX projMatrixInv;

	DEVICE->SetStreamSource(0, lightScreen->_vb, 0, lightScreen->vertexSize);
	DEVICE->SetVertexDeclaration(lightScreen->m_pDeclare);
	DEVICE->SetIndices(lightScreen->_ib);

	D3DXMatrixOrthoLH(&projMatrix, WIN_WIDTH, WIN_HEIGHT, 0, 1000);
	D3DXMatrixScaling(&worldMatrix, WIN_WIDTH, WIN_HEIGHT, 1);
	D3DXMatrixIdentity(&viewMatrix);


	AmbientLightShader->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
	AmbientLightShader->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
	AmbientLightShader->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));


	D3DXHANDLE albedoMap = AmbientLightShader->GetParameterByName(0, "AlbedoTex");
	AmbientLightShader->SetTexture(albedoMap, albedoRTTexture);

	//D3DXHANDLE specularMap = PointLightShader->GetParameterByName(0, "SpecularTex");
	//PointLightShader->SetTexture(specularMap, specularRTTextue);

	D3DXVECTOR4 ambientFactor = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1);

	AmbientLightShader->SetValue("AmbientFactor", &ambientFactor, sizeof(ambientFactor));


	AmbientLightShader->SetTechnique("AmbientLight");
	AmbientLightShader->Begin(0, 0);
	{
		AmbientLightShader->BeginPass(0);
		DEVICE->DrawIndexedPrimitive
		(
			D3DPT_TRIANGLELIST,
			0,
			0,
			4,
			0,
			2
		);
		AmbientLightShader->EndPass();

	}
	AmbientLightShader->End();
	//DEVICE->StretchRect(originSurface, NULL, stashRTSurface, NULL, D3DTEXF_NONE);
	DEVICE->StretchRect(lightRTSurface, NULL, stashRTSurface, NULL, D3DTEXF_NONE);

}

void DeferredWithBlur::DrawLight()
{
	for (int i = 0; i < lights.size(); i++)
	{
		LPD3DXEFFECT lightEffect = PointLightShader;
		switch (lights[i].Type)
		{
		case D3DLIGHT_POINT:
			lightEffect = PointLightShader;
			break;
		case D3DLIGHT_DIRECTIONAL :
			lightEffect = DirectionalLightShader;
			break;
		}

		D3DXMATRIX worldMatrix;
		D3DXMATRIX viewMatrix;
		D3DXMATRIX projMatrix;

		D3DXMATRIX viewMatrixInv;
		D3DXMATRIX projMatrixInv;

		DEVICE->SetStreamSource(0, lightScreen->_vb, 0, lightScreen->vertexSize);
		DEVICE->SetVertexDeclaration(lightScreen->m_pDeclare);
		DEVICE->SetIndices(lightScreen->_ib);

		D3DXMatrixOrthoLH(&projMatrix, WIN_WIDTH, WIN_HEIGHT, 0, 1000);
		D3DXMatrixScaling(&worldMatrix, WIN_WIDTH, WIN_HEIGHT, 1);
		D3DXMatrixIdentity(&viewMatrix);


		lightEffect->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
		lightEffect->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
		lightEffect->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));


		// set projection
		D3DXMatrixPerspectiveFovLH(
			&projMatrix, D3DX_PI * 0.25f,
			(float)WIN_WIDTH / (float)WIN_HEIGHT, 5.0f, 100.0f);

		// set view
		D3DXVECTOR3 position(0, 3, -10);
		//eyePosition = position;
		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
		D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);
		D3DXMatrixInverse(&viewMatrixInv, NULL, &viewMatrix);
		D3DXMatrixInverse(&projMatrixInv, NULL, &projMatrix);

		lightEffect->SetValue("TempViewMatrix", &viewMatrix, sizeof(viewMatrix));
		lightEffect->SetValue("TempProjMatrix", &projMatrix, sizeof(projMatrix));
		lightEffect->SetValue("ViewMatrixInv", &viewMatrixInv, sizeof(viewMatrixInv));
		lightEffect->SetValue("ProjMatrixInv", &projMatrixInv, sizeof(projMatrixInv));


		D3DXHANDLE depthMap = lightEffect->GetParameterByName(0, "DepthTex");
		lightEffect->SetTexture(depthMap, depthRTTexture);

		D3DXHANDLE albedoMap = lightEffect->GetParameterByName(0, "AlbedoTex");
		lightEffect->SetTexture(albedoMap, albedoRTTexture);

		D3DXHANDLE normalMap = lightEffect->GetParameterByName(0, "NormalTex");
		lightEffect->SetTexture(normalMap, normalRTTexture);


		D3DXHANDLE stashMap = lightEffect->GetParameterByName(0, "StashTex");
		lightEffect->SetTexture(stashMap, stashRTTexture);

		//D3DXHANDLE specularMap = PointLightShader->GetParameterByName(0, "SpecularTex");
		//PointLightShader->SetTexture(specularMap, specularRTTextue);


		//PointLightShader->SetValue("EyePosition", &eyePosition, sizeof(eyePosition));
		switch (lights[i].Type)
		{
		case D3DLIGHT_POINT:
			lightEffect->SetValue("LightPosition", &lights[i].Position, sizeof(lights[i].Position));
			lightEffect->SetValue("LightDiffuse", &lights[i].Diffuse, sizeof(lights[i].Diffuse));
			lightEffect->SetValue("LightAmbient", &lights[i].Ambient, sizeof(lights[i].Ambient));
			lightEffect->SetValue("LightRange", &lights[i].Range, sizeof(lights[i].Range));
			lightEffect->SetValue("LightConstant", &lights[i].Attenuation0, sizeof(lights[i].Attenuation0));
			lightEffect->SetValue("LightLinear", &lights[i].Attenuation1, sizeof(lights[i].Attenuation1));
			lightEffect->SetValue("LightExp", &lights[i].Attenuation2, sizeof(lights[i].Attenuation2));


			lightEffect->SetTechnique("PointLight");
			lightEffect->Begin(0, 0);
			{
				lightEffect->BeginPass(0);
				DEVICE->DrawIndexedPrimitive
				(
					D3DPT_TRIANGLELIST,
					0,
					0,
					4,
					0,
					2
				);
				lightEffect->EndPass();

			}
			lightEffect->End();
			break;
		case D3DLIGHT_DIRECTIONAL:
			int diffuseIntensity = 1;
			int specularIntensity = 1;
			int specularPower = 1;
			lightEffect->SetValue("LightDir", &lights[i].Direction, sizeof(lights[i].Direction));
			// position is camera eye
			lightEffect->SetValue("CameraEye",  &position, sizeof(position));
			lightEffect->SetValue("DiffuseIntensity", &diffuseIntensity, sizeof(diffuseIntensity));
			lightEffect->SetValue("SpecularIntensity", &specularIntensity, sizeof(specularIntensity));
			lightEffect->SetValue("SpecularPower", &specularPower, sizeof(specularPower));
			lightEffect->SetValue("Diffuse", &lights[i].Diffuse, sizeof(lights[i].Diffuse));
			lightEffect->SetValue("Specular", &lights[i].Diffuse, sizeof(lights[i].Specular));


			lightEffect->SetTechnique("DirectionalLight");
			lightEffect->Begin(0, 0);
			{
				lightEffect->BeginPass(0);
				DEVICE->DrawIndexedPrimitive
				(
					D3DPT_TRIANGLELIST,
					0,
					0,
					4,
					0,
					2
				);
				lightEffect->EndPass();

			}
			lightEffect->End();
			break;
		}

	
		//DEVICE->StretchRect(originSurface, NULL, stashRTSurface, NULL, D3DTEXF_NONE);
		DEVICE->StretchRect(lightRTSurface, NULL, stashRTSurface, NULL, D3DTEXF_NONE);


	}
}

void DeferredWithBlur::DrawBlur()
{

	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	D3DXMATRIX viewMatrixInv;
	D3DXMATRIX projMatrixInv;

	DEVICE->SetStreamSource(0, blurScreen->_vb, 0, blurScreen->vertexSize);
	DEVICE->SetVertexDeclaration(blurScreen->m_pDeclare);
	DEVICE->SetIndices(blurScreen->_ib);

	D3DXMatrixOrthoLH(&projMatrix, WIN_WIDTH, WIN_HEIGHT, 0, 1000);
	D3DXMatrixScaling(&worldMatrix, WIN_WIDTH, WIN_HEIGHT, 1);
	D3DXMatrixIdentity(&viewMatrix);


	BlurShader->SetValue("WorldMatrix", &worldMatrix, sizeof(worldMatrix));
	BlurShader->SetValue("ViewMatrix", &viewMatrix, sizeof(viewMatrix));
	BlurShader->SetValue("ProjMatrix", &projMatrix, sizeof(projMatrix));


	D3DXHANDLE lightMap = BlurShader->GetParameterByName(0, "SourceTex");
	BlurShader->SetTexture(lightMap, lightRTTexture);
	D3DXHANDLE blurMaskMap = BlurShader->GetParameterByName(0, "BlurMaskTex");
	BlurShader->SetTexture(blurMaskMap, blurMaskRTTexture);


	D3DXVECTOR2 sourceSize = D3DXVECTOR2(WIN_WIDTH, WIN_HEIGHT);
	int blurCount = 10;

	BlurShader->SetValue("SourceSize", &sourceSize, sizeof(sourceSize));
	BlurShader->SetValue("BlurCount", &blurCount, sizeof(blurCount));
	BlurShader->SetTechnique("SimpleBlur");
	
	BlurShader->Begin(0, 0);
	{
		BlurShader->BeginPass(0);
		DEVICE->DrawIndexedPrimitive
		(
			D3DPT_TRIANGLELIST,
			0,
			0,
			4,
			0,
			2
		);
		BlurShader->EndPass();

	}
	BlurShader->End();


}
