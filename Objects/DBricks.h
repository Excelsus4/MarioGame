#pragma once
#include "IBreakable.h"

class DBricks : public IBreakable {
public:
	DBricks(float posx, float posy, float indexx, float indexy);
	virtual ~DBricks();

	virtual void Bump(int force) override;
private:
	// Item Inside?
};