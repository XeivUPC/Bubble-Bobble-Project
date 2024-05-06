#pragma once
class IReseteable {
public:
	virtual void Reset() = 0;
	~IReseteable(){}
};