#include "stdafx.h"
#include "DBricks.h"

DBricks::DBricks(float posx, float posy, float indexx, float indexy):
	IBreakable(posx, posy, indexx, indexy)
{

}

DBricks::~DBricks()
{

}

void DBricks::Bump(int force)
{
	if (force > 1) {
		//TODO: TOTAL DESTRUCTION
		int destructionBreakpoint = 0;
	}
	else if (force == 1) {
		//TODO: That small bounce.
		int destructionBreakpoint = 0;
	}
}
