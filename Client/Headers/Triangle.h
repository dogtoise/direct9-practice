#pragma once


class Triangle
{

public:
	Triangle();
	~Triangle();


public :
	bool Setup();
	void Cleanup();

	bool Display(float timeDelta);

private :
	IDirect3DVertexBuffer9* triangleBuffer = nullptr;
};

