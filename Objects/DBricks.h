#pragma once
#include "IBreakable.h"

class DBricks : public IBreakable {
public:
	DBricks(float posx, float posy, float indexx, float indexy);
	virtual ~DBricks();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Bump(int force) override;

protected:
	void Bounce(float initial, float hooke);

private:
	// Item Inside?
	bool isBouncy;
	float origin;
	float velocity;
	float acceleration;
};