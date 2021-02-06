#include "stdafx.h"
#include "..\Headers\XFile.h"
#include "LightHelper.h"

XFile::XFile()
{
}


XFile::~XFile()
{
}

void XFile::Setup()
{

	ID3DXBuffer* adjBuffer = nullptr;
	ID3DXBuffer* materialBuffer = nullptr;
	DWORD numMaterials = 0;

	HRESULT hr = D3DXLoadMeshFromX
	(
		L"../../Resources/Fighter_A_LOD.x",
		D3DXMESH_DYNAMIC,
		DEVICE,
		&adjBuffer,
		&materialBuffer,
		0,
		&numMaterials,
		&mesh
	);
	
	assert(SUCCEEDED(hr));


	if (materialBuffer != 0 && numMaterials != 0)
	{
		D3DXMATERIAL* materials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();
	
		for (int i = 0; i < numMaterials; i++)
		{
			// the MatD3D property doesn't have an ambient value set
			// when its loaded, so set it now.
			materials[i].MatD3D.Ambient = materials[i].MatD3D.Diffuse;

			// save the ith material
			materialVec.push_back(materials[i].MatD3D);

			// check if the ith material has an associative texture 
			if (materials[i].pTextureFilename != 0)
			{
				// yes, load the texture for the ith subset
				IDirect3DTexture9* tex = nullptr;
				D3DXCreateTextureFromFile
				(
					DEVICE,
					(LPCWSTR)materials[i].pTextureFilename,
					&tex
				);

				// save the loaded texture
				textureVec.push_back(tex);
			}
			else
			{
				textureVec.push_back(0);
			}
		}
	}
	materialBuffer->Release();

	// optimize the mesh
	hr = mesh->OptimizeInplace
	(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)adjBuffer->GetBufferPointer(),
		0, 0, 0
	);
	adjBuffer->Release();

	assert(SUCCEEDED(hr));

	// set texture filter
	DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	DEVICE->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// set light

	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXCOLOR col(1.0f, 1.0f, 1.0f, 1.0f);
	D3DLIGHT9 light = LightHelper::InitDirectionalLight(&dir, &col);

	DEVICE->SetLight(0, &light);
	DEVICE->LightEnable(0, true);
	DEVICE->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	DEVICE->SetRenderState(D3DRS_SPECULARENABLE, true);


	//
	// Set camera.
	//

	D3DXVECTOR3 pos(4.0f, 4.0f, -13.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXMATRIX V;
	D3DXMatrixLookAtLH(
		&V,
		&pos,
		&target,
		&up);

	DEVICE->SetTransform(D3DTS_VIEW, &V);

	//
	// Set projection matrix.
	//

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f, // 90 - degree
		(float)WIN_WIDTH / (float)WIN_HEIGHT,
		1.0f,
		1000.0f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);

}

void XFile::Cleanup()
{
	mesh->Release();

	for (int i = 0; i < textureVec.size(); i++)
		textureVec[i]->Release();
}

void XFile::Display()
{
	static float y = 0.0f;
	D3DXMATRIX yRot;
	D3DXMatrixRotationY(&yRot, y);
	y += 0.001f;

	if (y >= 6.28f)
		y = 0.0f;

	D3DXMATRIX World = yRot;

	DEVICE->SetTransform(D3DTS_WORLD, &World);

	for (int i = 0; i < materialVec.size(); i++)
	{
		DEVICE->SetMaterial(&materialVec[i]);
		DEVICE->SetTexture(0, textureVec[i]);
		mesh->DrawSubset(i);
	}


}
