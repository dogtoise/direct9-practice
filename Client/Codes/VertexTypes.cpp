#include "stdafx.h"
#include "..\Headers\VertexTypes.h"

const DWORD Vertex::FVF = D3DFVF_XYZ;

const DWORD ColorVertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

const DWORD PyramidVertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL;

const DWORD TextureVertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

const DWORD MultiTexVertex::FVF = D3DFVF_XYZ | D3DFVF_TEX3;