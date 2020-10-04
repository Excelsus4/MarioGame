#pragma once
#include "stdafx.h"
#include "Bricks.h"
#include "Extra/IDisposable.h"

class IBreakable : public Bricks, public IDisposable {
public:
	IBreakable(float posx, float posy, float indexx, float indexy) :Bricks(posx, posy, indexx, indexy) {};

	virtual void Bump(int force) = 0;
};