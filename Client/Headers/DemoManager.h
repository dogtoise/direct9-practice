#pragma once

class IDemo;
class DemoManager
{
public:
	DemoManager();
	~DemoManager();

	void Push(IDemo* demo);
	void SetupDemo();
	void CleanupDemo();
	void DisplayDemo();
private :
	std::vector<IDemo*> demos;

};

