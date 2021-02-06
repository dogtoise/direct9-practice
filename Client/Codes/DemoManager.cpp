#include "stdafx.h"
#include "..\Headers\DemoManager.h"
#include "IDemo.h"

DemoManager::DemoManager()
{
}


DemoManager::~DemoManager()
{
}

void DemoManager::Push(IDemo * demo)
{
	demos.push_back(demo);
}

void DemoManager::SetupDemo()
{
	for (auto demo : demos)
		demo->Setup();
}

void DemoManager::CleanupDemo()
{
	for (auto demo : demos)
		demo->Cleanup();
}

void DemoManager::DisplayDemo()
{
	for (auto demo : demos)
		demo->Display();
}
