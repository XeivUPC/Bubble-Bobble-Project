#pragma once
class IRendereable {
public:
	virtual void Render() = 0;
	~IRendereable() {}
};