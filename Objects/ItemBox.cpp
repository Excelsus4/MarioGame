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
	Bounce(160.0f, -1280.0f);
}

void ItemBox::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (isBouncy) {
		D3DXVECTOR2 pos = Position();
		velocity += acceleration * Timer->Elapsed();
		pos.y += velocity * Timer->Elapsed();
		if (pos.y <= origin) {
			pos.y = origin;
			isBouncy = false;
		}
		Position(pos);
	}

	__super::Update(V, P);
}

void ItemBox::Render()
{
	//TODO: if Item is there, then Play the question animation
	//TODO: if not, then play the __super::Render()
	__super::Render();
}

void ItemBox::Bounce(float initial, float hooke)
{
	velocity = initial;
	acceleration = hooke;
	isBouncy = true;
	origin = Position().y;
}
