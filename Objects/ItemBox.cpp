#include "stdafx.h"
#include "ItemBox.h"

ItemBox::ItemBox(float posx, float posy, float indexx, float indexy):
	IBreakable(posx, posy, indexx, indexy)
{
}

ItemBox::~ItemBox()
{
}

void ItemBox::Bump(int force)
{
	//If Item inside, spit the item and change sprite
}

void ItemBox::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	__super::Update(V, P);
}

void ItemBox::Render()
{
	//TODO: if Item is there, then Play the question animation
	//TODO: if not, then play the __super::Render()
	__super::Render();
}
