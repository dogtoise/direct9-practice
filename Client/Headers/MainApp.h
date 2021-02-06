#pragma once

class CMainApp final
{
public:
	explicit CMainApp();
	~CMainApp();

public :
	HRESULT ReadyMainApp();
	void UpdateMainApp();
	void LateUpdateMainApp();
	void RenderMainApp();
	void ReleaseMainApp();

private :
	class CGraphicDevice* m_pGraphicDevice;

private :
	// test
	//class Triangle * triangle;
	//class Cube* cube;
	//class Teapot* teapot;
	class DemoManager* demoManager;
};

