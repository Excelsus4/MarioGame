#pragma once
#include "stdafx.h"
#include "Extra/IDisposable.h"
#include "Viewer/IViewDrivenLife.h"

class IMario {
public:
	virtual void Damage(int damage) = 0;
	virtual void Grow(int level) = 0;
	virtual void Bounce(int power) = 0;
};

class Interact : public IDisposable, public IViewDrivenLife {
public:
	Interact() {};
	virtual ~Interact() {};

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P, World* world) =0;
	virtual void Render() = 0;

	virtual void Interact_Up(IMario* target) = 0;
	virtual void Interact_Side(IMario* target) = 0;

	virtual D3DXVECTOR2 Position() const = 0;
	virtual D3DXVECTOR2 Size() const = 0;

};