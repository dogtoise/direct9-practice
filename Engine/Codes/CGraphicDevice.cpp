#include "Engine.h"
#include "CGraphicDevice.h"

CGraphicDevice* CGraphicDevice::m_pInstance = nullptr;

CGraphicDevice::CGraphicDevice()
{
}

CGraphicDevice::CGraphicDevice(const CGraphicDevice & rObject)
{
	ReleaseGraphicDevice();
}

HRESULT CGraphicDevice::ReadyGraphicDevice(WINMODE eMode, HWND hWnd)
{
	// ��ġ�� ���� ������ �����ؼ� �����͸� ������ ����ü. 
		// �ܿ� �ʿ�� ����. ����. 
	D3DCAPS9 DeviceCap;
	ZeroMemory(&DeviceCap, sizeof(D3DCAPS9));
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCap)))
	{
		return E_FAIL;
	}
	DWORD vp = 0;
	// vVERTEXPROCESSING - ���� ��ȯ + �������� ���� ���ؽ� ���μ����̶� �θ�. 
	// �̰� ���� ��쿡�� ��κ��� ��ǻ�Ϳ��� ������ �Ǵ� ���� else ��ü�� �ʿ� ���� �����̱⵵ ������ .
	// Ȥ�ó���°� ���ó���� ���� �� ���� �ֱ� ������. 
	// ������� ���� ��ȯ�� �ϵ����(��ġ����)���� ó���� ������ �ƴϸ� �����ڰ� ����Ʈ����(�ϳ� ����)���� ó���� �������� ���Ѵ�. 
	if (DeviceCap.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferWidth = 800;
	d3dpp.BackBufferHeight = 600;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;// ���⼭ 1�� �� 2���� ����۸� ����ϰڴ�. �� ����Ʈ�� �Ѱ� ����. �ű⿡ +1 �� 

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // ���� ü�� ����� ����ϰڴ�. -> ������۸��� ���� ȣȯ����. 
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = TRUE;// TRUE�� ��� â���, FALSE�� ��� ��üȭ�� ��� MFC���� â���� ���. 
	d3dpp.EnableAutoDepthStencil = eMode;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;


	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &d3dpp, &m_pDevice)))
	{
		return E_FAIL;
	}
	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		return E_FAIL;
	}
	D3DXFONT_DESCW tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));
	tFontInfo.Height = 20;
	tFontInfo.Width = 10;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"���� ���");

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		return E_FAIL;
	}
	if (FAILED(D3DXCreateLine(m_pDevice, &m_pLine)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CGraphicDevice::ReleaseGraphicDevice()
{
	if (m_pFont)
		m_pFont->Release();
	if (m_pSprite)
		m_pSprite->Release();
	if (m_pDevice)
		m_pDevice->Release();
	if (m_pSDK)
		m_pSDK->Release();
}



void CGraphicDevice::RenderBegin()
{
	m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	m_pDevice->BeginScene();
	//m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CGraphicDevice::RenderEnd(HWND hWnd)
{
	m_pDevice->EndScene();
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);
}
