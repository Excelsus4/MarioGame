#include "stdafx.h"
#include "Map.h"

void Map::MapGen(vector<Bricks*>* brV, vector<Bricks*>* fbrV, vector<Bricks*>* nbrV)
{
	for (int i = 0; i < 69; i++) {
		fbrV->push_back(new Bricks(D3DXVECTOR2(i * 16 + 8, 16), D3DXVECTOR2(0, 2)));
		nbrV->push_back(new Bricks(D3DXVECTOR2(i * 16 + 8, 0), D3DXVECTOR2(0, 2)));
	}


}
