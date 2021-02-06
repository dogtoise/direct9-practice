#pragma once
class Teapot
{
public:
	Teapot();
	~Teapot();

	void Setup();
	void Cleanup();
	void Display();
	

private :
	ID3DXMesh* teapotMesh = 0;
};

