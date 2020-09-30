#pragma once
#include "Item.h"

class ShiftingItem : public Item {
public:
	ShiftingItem();
	virtual ~ShiftingItem();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
private:

};