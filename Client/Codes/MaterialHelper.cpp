#include "stdafx.h"
#include "..\Headers\MaterialHelper.h"


MaterialHelper::MaterialHelper()
{
}


MaterialHelper::~MaterialHelper()
{
}
const D3DMATERIAL9 MaterialHelper::WHITE_MTRL = InitMaterial(WHITE, WHITE, WHITE, BLACK, 2.0f);
const D3DMATERIAL9 MaterialHelper::RED_MTRL = InitMaterial(RED, RED, RED, BLACK, 2.0f);
const D3DMATERIAL9 MaterialHelper::GREEN_MTRL = InitMaterial(GREEN, GREEN, GREEN, BLACK, 2.0f);
const D3DMATERIAL9 MaterialHelper::BLUE_MTRL = InitMaterial(BLUE, BLUE, BLUE, BLACK, 2.0f);
const D3DMATERIAL9 MaterialHelper::YELLOW_MTRL = InitMaterial(YELLOW, YELLOW, YELLOW, BLACK, 2.0f);