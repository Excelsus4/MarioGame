#pragma once
#include "stdafx.h"

class IMario {
public:
	virtual void Damage(int damage) = 0;
	virtual void Grow(int level) = 0;
};

class Interact {
public:
	Interact() {};
	virtual ~Interact() {};

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P, World* world) =0;
	virtual void Render() = 0;

	virtual void Interact_Up(IMario* target) = 0;
	virtual void Interact_Left(IMario* target) = 0;
	virtual void Interact_Right(IMario* target) = 0;

	virtual D3DXVECTOR2 Position() const = 0;
	virtual D3DXVECTOR2 Size() const = 0;

};