#include "stdafx.h"
#include "..\Headers\MeshesDemo.h"


MeshesDemo::MeshesDemo()
{
}


MeshesDemo::~MeshesDemo()
{
}

void MeshesDemo::Setup()
{
	// create the objects

	D3DXCreateTeapot
	(
		DEVICE,
		&Objects[0],
		0
	);

	D3DXCreateBox
	(
		DEVICE,
		2.0f, // width
		2.0f, // height
		2.0f, // depth
		&Objects[1],
		0
	);

	D3DXCreateCylinder
	(
		DEVICE,
		1.0f, // radius at negative z end
		1.0f, // radius at positive z end
		3.0f, // length of cylinder
		10, // slices
		10, // stacks
		&Objects[2],
		0
	);

	D3DXCreateTorus(
		DEVICE,
		1.0f, // inner radius
		3.0f, // outer radius
		10,   // sides
		10,   // rings
		&Objects[3],
		0);

	D3DXCreateSphere(
		DEVICE,
		1.0f, // radius
		10,   // slices
		10,   // stacks
		&Objects[4],
		0);


	D3DXMatrixTranslation(&ObjWorldMatrices[0], 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&ObjWorldMatrices[1], -5.0f, 0.0f, 5.0f);
	D3DXMatrixTranslation(&ObjWorldMatrices[2], 5.0f, 0.0f, 5.0f);
	D3DXMatrixTranslation(&ObjWorldMatrices[3], -5.0f, 0.0f, -5.0f);
	D3DXMatrixTranslation(&ObjWorldMatrices[4], 5.0f, 0.0f, -5.0f);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH
	(
		&proj,
		D3DX_PI* 0.5f, // 90 degree
		WIN_WIDTH / WIN_HEIGHT,
		1.0f, 
		1000.0f
	);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);

	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);


}

void MeshesDemo::Cleanup()
{
	for (int i = 0; i < 5; i++)
		Objects[i]->Release();
}

void MeshesDemo::Display()
{
	// Animate the camera:
	// The camera will circle around the center of the scene.  We use the
	// sin and cos functions to generate points on the circle, then scale them
	// by 10 to further the radius.  In addition the camera will move up and down
	// as it circles about the scene.
	static float angle = (3.0f * D3DX_PI) / 2.0f;
	static float cameraHeight = 0.0f;
	static float cameraHeightDirection = 5.0f;

	D3DXVECTOR3 position(cosf(angle) * 10.0f, cameraHeight, sinf(angle) * 10.0f);

	// the camera is targetted at the origin of the world
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);

	// the worlds up vector
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &up);
	DEVICE->SetTransform(D3DTS_VIEW, &viewMatrix);

	angle += 0.001f;
	if (angle >= 6.28f)
		angle = 0.0f;

	// compute the height of the camera for the next frame
	cameraHeight += cameraHeightDirection * 0.001f;
	if (cameraHeight >= 10.0f)
		cameraHeightDirection = -5.0f;

	if (cameraHeight <= -10.0f)
		cameraHeightDirection = 5.0f;

	// Draw the Scene

	for (int i = 0; i < 5; i++)
	{
		// Set the world matrix that positions the object.
		DEVICE->SetTransform(D3DTS_WORLD, &ObjWorldMatrices[i]);

		// Draw the object  using the previously set world matrix.
		Objects[i]->DrawSubset(0);
	}

}
