#pragma once
#include "stdafx.h"
#include "Particle.h"

class IDisposable {
public:
	IDisposable() :isTrash(false) {};
	virtual ~IDisposable() {};

	virtual void OnDisposal(vector<Particle*>* pVector) = 0;
public:
	bool isTrash;
};