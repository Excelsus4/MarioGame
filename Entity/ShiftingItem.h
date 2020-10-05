#pragma once
#include "Item.h"
#include "IDrifting.h"

class ShiftingItem : public Item, public IDrifting {
public:
	ShiftingItem(D3DXVECTOR2 pos);
	virtual ~ShiftingItem();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P, World* world) override;

	virtual void Position(float x, float y) override;
	virtual void Position(D3DXVECTOR2 vec) override;
	virtual D3DXVECTOR2 Position() const override;

	virtual D3DXVECTOR2 Size() const override;
private:

};