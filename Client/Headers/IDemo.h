#pragma once
class IDemo abstract
{
public:
	virtual void Setup() = 0;
	virtual void Cleanup() = 0;
	virtual void Display() = 0;

};

