#include "stdafx.h"
#include "MainApp.h"
#include "CGraphicDevice.h"

#include "Triangle.h"
#include "Cube.h"
#include "Teapot.h"
#include "DemoManager.h"
#include "MeshesDemo.h"
#include "ColorTriangle.h"
#include "LitPyramid.h"
#include "DirectionalLight.h"
#include "TexQuad.h"
#include "TexCube.h"
#include "VSTransform.h"
#include "AddressModes.h"
#include "MaterialAlpha.h"
#include "TextureAlpha.h"
#include "StencilMirror.h"
#include "StencilShadow.h"
#include "PSMultiTexture.h"
#include "XFile.h"

CMainApp::CMainApp()
	: m_pGraphicDevice(CGraphicDevice::Get())
{

}


CMainApp::~CMainApp()
{
	
}

HRESULT CMainApp::ReadyMainApp()
{
	if (m_pGraphicDevice->ReadyGraphicDevice(CGraphicDevice::MODE_WIN, g_hWnd))
	{
		return E_FAIL;
	}
	//cube = new Cube();
	//cube->Setup();
	//teapot = new Teapot();
	//teapot->Setup();
	demoManager = new DemoManager();
	// todo : demoManager->push(new Teapot)
	//demoManager->Push(new MeshesDemo());
	//demoManager->Push(new ColorTriangle());
	//demoManager->Push(new LitPyramid());
	//demoManager->Push(new DirectionalLight());
	//demoManager->Push(new TexQuad());
	//demoManager->Push(new TexCube());
	//demoManager->Push(new VSTransform());
	//demoManager->Push(new AddressModes());
	//demoManager->Push(new MaterialAlpha());
	//demoManager->Push(new TextureAlpha());
	//demoManager->Push(new StencilMirror());
	//demoManager->Push(new StencilShadow());
	//demoManager->Push(new PSMultiTexture());
	demoManager->Push(new XFile());
	demoManager->SetupDemo();

	return S_OK;
}

void CMainApp::UpdateMainApp()
{
}

void CMainApp::LateUpdateMainApp()
{
}

void CMainApp::RenderMainApp()
{
	m_pGraphicDevice->RenderBegin();
	//triangle->Display(0);
	//cube->Display();
	//teapot->Display();
	demoManager->DisplayDemo();
	m_pGraphicDevice->RenderEnd();
}

void CMainApp::ReleaseMainApp()
{
	m_pGraphicDevice->Destroy();
	//triangle->Cleanup();
	//cube->Cleanup();
	//teapot->Cleanup();
	demoManager->CleanupDemo();
}
