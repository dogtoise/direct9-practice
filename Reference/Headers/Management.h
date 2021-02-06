#pragma once
#ifndef __MANAGEMENT_H__

#include "Engine_Define.h"

class ENGINE_DLL CManagement
{
	DECLARE_SINGLETON(CManagement)

private:
	CManagement();
	~CManagement();


};

#define __MANAGEMENT_H__
#endif
