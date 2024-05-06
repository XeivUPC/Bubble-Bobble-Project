#pragma once
class IDebugeable {
public:
	virtual void Debug() = 0;
	~IDebugeable() {}
};