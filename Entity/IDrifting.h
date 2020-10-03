#pragma once
#include "IGravity.h"

class IDrifting {
public:
	IDrifting(D3DXVECTOR2 speed);
	virtual ~IDrifting() {}

	virtual void Update(World* world);

	virtual void Position(float x, float y) = 0;
	virtual void Position(D3DXVECTOR2 vec) = 0;
	virtual D3DXVECTOR2 Position() const = 0;

	virtual D3DXVECTOR2 Size() const = 0;

protected:
	D3DXVECTOR2 velocity;
};