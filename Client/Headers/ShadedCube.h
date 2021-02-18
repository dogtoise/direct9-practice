#pragma once


class ShadedCube
{
public:
	ShadedCube();
	~ShadedCube();


	IDirect3DVertexBuffer9* _vb;
	IDirect3DIndexBuffer9* _ib;
	IDirect3DVertexDeclaration9* m_pDeclare;
	int numVertex = 24;
	int vertexSize;
	int primNum = 12;
};

