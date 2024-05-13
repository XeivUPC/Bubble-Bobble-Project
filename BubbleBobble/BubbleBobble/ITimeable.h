#pragma once
class ITimeable {
public:
	~ITimeable() {}
protected:
	float internalTimer = 0;

};