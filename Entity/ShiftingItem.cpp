#include "stdafx.h"
#include "ShiftingItem.h"

ShiftingItem::ShiftingItem(D3DXVECTOR2 pos):
	Item(pos), IDrifting(D3DXVECTOR2(40.0f, 0.0f))
{
	InitializeAsMushroom();
}

ShiftingItem::~ShiftingItem()
{
}

void ShiftingItem::Update(D3DXMATRIX & V, D3DXMATRIX & P, World * world)
{
	IDrifting::Update(world);
	Item::Update(V, P, world);
}

void ShiftingItem::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void ShiftingItem::Position(D3DXVECTOR2 vec)
{
	Item::Position(vec);
}

D3DXVECTOR2 ShiftingItem::Position() const
{
	return Item::Position();
}

D3DXVECTOR2 ShiftingItem::Size() const
{
	return Item::Size();
}
