#pragma once
#include "IDemo.h"


class AddressModes : public IDemo
{
public:
	AddressModes();
	~AddressModes();

	// Inherited via IDemo
	virtual void Setup() override;
	virtual void Cleanup() override;
	virtual void Display() override;

private :
	IDirect3DVertexBuffer9* quadBuffer = nullptr;
	IDirect3DTexture9 *texture;
};

