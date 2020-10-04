#pragma once

class IViewDrivenLife {
public:
	IViewDrivenLife() :isAlive(false) {}
	virtual ~IViewDrivenLife() {}

	virtual D3DXVECTOR2 Position() const = 0;
	virtual D3DXVECTOR2 Size() const = 0;
public:
	bool isAlive;
};