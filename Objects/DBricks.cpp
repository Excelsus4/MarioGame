#include "stdafx.h"
#include "DBricks.h"

DBricks::DBricks(float posx, float posy, float indexx, float indexy):
	IBreakable(posx, posy, indexx, indexy), isBouncy(false)
{

}

DBricks::~DBricks()
{

}

void DBricks::Update(D3DXMATRIX & V, D3DXMATRIX & P)
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

void DBricks::Bump(int force)
{
	if (force > 1) {
		//TODO: TOTAL DESTRUCTION
		int destructionBreakpoint = 0;
	}
	else if (force == 1) {
		//That small bounce.
		Bounce(160.0f, -1280.0f);
	}
}

void DBricks::Bounce(float initial, float hooke)
{
	velocity = initial;
	acceleration = hooke;
	isBouncy = true;
	origin = Position().y;
}
