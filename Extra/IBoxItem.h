#pragma once
#include "stdafx.h"

class IBoxItem {
public:
	IBoxItem() {}
	virtual ~IBoxItem() {}

	virtual void Activate(D3DXVECTOR2 origin) = 0;
};