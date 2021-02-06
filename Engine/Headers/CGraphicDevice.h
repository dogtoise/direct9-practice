#pragma once
#include "Engine_Define.h"
class ENGINE_DLL CGraphicDevice final
{
public :
	enum WINMODE {MODE_FULL, MODE_WIN};

public :
	static CGraphicDevice* Get()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CGraphicDevice;
		return m_pInstance;
	}
	static void Destroy()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private :
	static CGraphicDevice* m_pInstance;

private :
	explicit CGraphicDevice();
	explicit CGraphicDevice(const CGraphicDevice& rObject);
	void operator=(const CGraphicDevice& rObject) {};

public :
	LPDIRECT3DDEVICE9 GetDevice() { return m_pDevice; }
	
public :
	HRESULT ReadyGraphicDevice(WINMODE eMode, HWND hWnd);
	void ReleaseGraphicDevice();
	void RenderBegin();
	void RenderEnd(HWND hWnd = nullptr);

private :
	LPDIRECT3D9 m_pSDK;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXSPRITE m_pSprite;
	LPD3DXFONT m_pFont;
	LPD3DXLINE m_pLine;
};

