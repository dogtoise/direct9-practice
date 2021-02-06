#pragma once

#include "IDemo.h"


class XFile : public IDemo
{
public:
	XFile();
	~XFile();

	

	// Inherited via IDemo
	virtual void Setup() override;

	virtual void Cleanup() override;

	virtual void Display() override;


private :

	ID3DXMesh * mesh = nullptr;
	std::vector<D3DMATERIAL9> materialVec;
	std::vector<IDirect3DTexture9*> textureVec;


};

