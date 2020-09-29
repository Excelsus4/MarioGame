#include "stdafx.h"
#include "Map.h"

Map::Map(vector<Bricks*>* brV, vector<Bricks*>* fbrV, vector<Bricks*>* nbrV, vector<IBreakable*>* pbrV):
	brV(brV), fbrV(fbrV), nbrV(nbrV), pbrV(pbrV)
{
}

Map::~Map()
{
}

void Map::GenerateMap()
{
	//TODO: Create Map HERE
	GenerateGround(D3DXVECTOR2(0, 0), 69);
	{
		GenerateHedge(D3DXVECTOR2(0, 2), 2);
		GenerateCloud(D3DXVECTOR2(8, 10), 1);
		GenerateBush(D3DXVECTOR2(12, 2), 3);
		GenerateHedge(D3DXVECTOR2(17, 2), 1);
		GenerateBush(D3DXVECTOR2(23, 2), 1);
		GenerateCloud(D3DXVECTOR2(27, 10), 3);
		GeneratePipe(D3DXVECTOR2(28, 2), 2);

		{
			// Platforms
			GenerateBox(D3DXVECTOR2(17, 5));

			GenerateBrick(D3DXVECTOR2(20, 5));
			GenerateBox(D3DXVECTOR2(21, 5));
			GenerateBrick(D3DXVECTOR2(22, 5));
			GenerateBox(D3DXVECTOR2(23, 5));
			GenerateBrick(D3DXVECTOR2(24, 5));

			GenerateBox(D3DXVECTOR2(22, 9));

			GenerateCloud(D3DXVECTOR2(19, 11), 1);
		}

		GenerateCloud(D3DXVECTOR2(36, 11), 2);

		GeneratePipe(D3DXVECTOR2(38, 2), 3);
		GenerateBush(D3DXVECTOR2(41, 2), 2);
		GeneratePipe(D3DXVECTOR2(46, 2), 4);
		GenerateHedge(D3DXVECTOR2(48, 2), 2);
		GenerateCloud(D3DXVECTOR2(56, 10), 1);
		GeneratePipe(D3DXVECTOR2(57, 2), 4);
		GenerateBush(D3DXVECTOR2(59, 2), 3);
		GenerateHedge(D3DXVECTOR2(64, 2), 1);

		{
			// Extra Life
			GenerateBox(D3DXVECTOR2(64, 6));
		}

		GenerateCloud(D3DXVECTOR2(67, 11), 1);
	}

	GenerateGround(D3DXVECTOR2(71, 0), 15); 
	{
		GenerateBush(D3DXVECTOR2(71, 2), 1);

		{
			GenerateCloud(D3DXVECTOR2(75, 10), 3);

			//Platforms
			GenerateBrick(D3DXVECTOR2(77, 5));
			GenerateBox(D3DXVECTOR2(78, 5));
			GenerateBrick(D3DXVECTOR2(79, 5));

			GenerateBrick(D3DXVECTOR2(80, 9),8);

			GenerateCloud(D3DXVECTOR2(84, 11), 2);
		}
	}

	GenerateGround(D3DXVECTOR2(89, 0), 64);
	{
		GenerateBush(D3DXVECTOR2(89, 2), 2);

		{
			//Platforms
			GenerateBrick(D3DXVECTOR2(91, 9), 3);
			GenerateBox(D3DXVECTOR2(94, 9));

			GenerateBrick(D3DXVECTOR2(94, 5));

			GenerateBrick(D3DXVECTOR2(100, 5));
			GenerateBox(D3DXVECTOR2(101, 5));

			GenerateCloud(D3DXVECTOR2(104, 10), 1);

			GenerateBox(D3DXVECTOR2(106, 5));
			GenerateBox(D3DXVECTOR2(109, 5));
			GenerateBox(D3DXVECTOR2(112, 5));

			GenerateBox(D3DXVECTOR2(109, 9));
		}

		GenerateHedge(D3DXVECTOR2(96, 2), 2);
		GenerateBush(D3DXVECTOR2(107, 2), 2);
		GenerateHedge(D3DXVECTOR2(112, 2), 1);

		GenerateCloud(D3DXVECTOR2(115, 11), 1);

		GenerateBrick(D3DXVECTOR2(118, 5));

		GenerateBush(D3DXVECTOR2(119, 2), 1);

		GenerateBrick(D3DXVECTOR2(121, 9), 3);

		GenerateCloud(D3DXVECTOR2(123, 10), 3);

		GenerateBrick(D3DXVECTOR2(128, 9));
		GenerateBox(D3DXVECTOR2(129, 9));
		GenerateBox(D3DXVECTOR2(130, 9));
		GenerateBrick(D3DXVECTOR2(131, 9));

		GenerateCloud(D3DXVECTOR2(132, 11), 2);

		GenerateBrick(D3DXVECTOR2(129, 5), 2);

		GenerateStair(D3DXVECTOR2(134, 2), D3DXVECTOR2(1, 1), 4);
		GenerateStairFill(D3DXVECTOR2(135, 2), D3DXVECTOR2(1, 1), 2);
		GenerateStair(D3DXVECTOR2(137, 2), D3DXVECTOR2(0, 1), 3);
		GenerateBush(D3DXVECTOR2(137, 2), 2);
		GenerateStair(D3DXVECTOR2(140, 2), D3DXVECTOR2(0, 1), 3);
		GenerateStairFill(D3DXVECTOR2(141, 3), D3DXVECTOR2(1, -1), 2);
		GenerateStair(D3DXVECTOR2(140, 5), D3DXVECTOR2(1, -1), 4);

		GenerateHedge(D3DXVECTOR2(144, 2), 2);
		GenerateStair(D3DXVECTOR2(148, 2), D3DXVECTOR2(1, 1), 4);
		GenerateStairFill(D3DXVECTOR2(149, 2), D3DXVECTOR2(1, 1), 3);
		GenerateStair(D3DXVECTOR2(152, 2), D3DXVECTOR2(0, 1), 4);

		GenerateCloud(D3DXVECTOR2(152, 10), 1);
	}

	GenerateGround(D3DXVECTOR2(155, 0), 56);
	{
		GenerateStair(D3DXVECTOR2(155, 5), D3DXVECTOR2(1, -1), 4);
		GenerateStairFill(D3DXVECTOR2(156, 3), D3DXVECTOR2(1, -1), 2);
		GenerateStair(D3DXVECTOR2(155, 2), D3DXVECTOR2(0, 1), 3);

		GenerateBush(D3DXVECTOR2(158, 2), 0);
		GenerateHedge(D3DXVECTOR2(160, 2), 1);

		GeneratePipe(D3DXVECTOR2(163, 2), 2);
		GenerateCloud(D3DXVECTOR2(163, 11), 1);

		GenerateBush(D3DXVECTOR2(167, 2), 1);

		GenerateBrick(D3DXVECTOR2(168, 5), 2);
		GenerateBox(D3DXVECTOR2(170, 5));
		GenerateBrick(D3DXVECTOR2(171, 5));
		GenerateCloud(D3DXVECTOR2(171, 10), 3);

		GeneratePipe(D3DXVECTOR2(179, 2), 2);
		GenerateCloud(D3DXVECTOR2(180, 11), 2);
		GenerateStair(D3DXVECTOR2(181, 2), D3DXVECTOR2(1, 1), 8);
		GenerateStairFill(D3DXVECTOR2(182, 2), D3DXVECTOR2(1, 1), 7);
		GenerateStair(D3DXVECTOR2(189, 2), D3DXVECTOR2(0, 1), 8);

		GenerateHedge(D3DXVECTOR2(192, 2), 2);

		GenerateCloud(D3DXVECTOR2(200, 10), 1);

		GenerateBush(D3DXVECTOR2(206, 2), 0);
		GenerateHedge(D3DXVECTOR2(208, 2), 1);

		GenerateFlag(D3DXVECTOR2(198, 2));
		GenerateCastle(D3DXVECTOR2(202, 2));
	}
}

void Map::GenerateGround(D3DXVECTOR2 p, int l)
{
	for (int i = 0; i < l; i++) {
		fbrV->push_back(new Bricks(i + p.x, 1, 0, 0));
		nbrV->push_back(new Bricks(i + p.x, 0, 0, 0));
	}
}

void Map::GeneratePipe(D3DXVECTOR2 p, int h)
{
	//First Pipe
	for (int i = 0; i < h - 1; ++i) {
		brV->push_back(new Bricks(p.x, p.y + i, 0, 9));
		brV->push_back(new Bricks(p.x + 1, p.y + i, 1, 9));
	}
	brV->push_back(new Bricks(p.x, p.y + h - 1, 0, 8));
	brV->push_back(new Bricks(p.x + 1, p.y + h - 1, 1, 8));
}

void Map::GenerateBush(D3DXVECTOR2 p, int l)
{
	//Single Bush
	nbrV->push_back(new Bricks(p.x, p.y, 11, 9));
	for(int i=0; i < l;i++)
		nbrV->push_back(new Bricks(p.x+i+1, p.y, 12, 9));
	nbrV->push_back(new Bricks(p.x+l+1, p.y, 13, 9));
}

void Map::GenerateHedge(D3DXVECTOR2 p, int h)
{
	switch (h) {
	case 1:
		nbrV->push_back(new Bricks(p.x, p.y, 8, 8));
		nbrV->push_back(new Bricks(p.x+1, p.y+1, 9, 8));
		nbrV->push_back(new Bricks(p.x+2, p.y, 10, 8));
		nbrV->push_back(new Bricks(p.x+1, p.y, 8, 9));
		break;
	case 2:
		nbrV->push_back(new Bricks(p.x, p.y, 8, 8));
		nbrV->push_back(new Bricks(p.x + 1, p.y + 1, 8, 8));
		nbrV->push_back(new Bricks(p.x + 2, p.y + 2, 9, 8));
		nbrV->push_back(new Bricks(p.x + 3, p.y + 1, 10, 8));
		nbrV->push_back(new Bricks(p.x + 4, p.y, 10, 8));
		nbrV->push_back(new Bricks(p.x + 1, p.y, 8, 9));
		nbrV->push_back(new Bricks(p.x + 2, p.y + 1, 8, 9));
		nbrV->push_back(new Bricks(p.x + 2, p.y, 9, 9));
		nbrV->push_back(new Bricks(p.x + 3, p.y, 10, 9));
		break;
	}
}

void Map::GenerateBrick(D3DXVECTOR2 p)
{
	pbrV->push_back(new DBricks(p.x, p.y, 1, 0));
}

void Map::GenerateBrick(D3DXVECTOR2 p, int l)
{
	for (int i = 0; i < l; i++)
		pbrV->push_back(new DBricks(p.x + i, p.y, 1, 0));
}

void Map::GenerateBox(D3DXVECTOR2 p)
{
	pbrV->push_back(new ItemBox(p.x, p.y, 26, 0));
}

void Map::GenerateStair(D3DXVECTOR2 p, D3DXVECTOR2 stride, int l)
{
	for (int i = 0; i < l; i++) {
		brV->push_back(new Bricks(p.x + i * stride.x, p.y + i * stride.y, 0, 1));
	}
}

void Map::GenerateStairFill(D3DXVECTOR2 p, D3DXVECTOR2 stride, int l)
{
	for (int i = 0; i < l; i++) {
		for (int j = p.y + stride.y*i; j >= 2; j--) {
			nbrV->push_back(new Bricks(p.x + i * stride.x, j, 0, 1));
		}
	}
}

void Map::GenerateFlag(D3DXVECTOR2 p)
{
	nbrV->push_back(new Bricks(p.x, p.y, 0, 1));
	for (int i = 0; i < 9; i++) {
		nbrV->push_back(new Bricks(p.x, p.y + i + 1, 16, 9));
	}
	nbrV->push_back(new Bricks(p.x, p.y + 10, 16, 8));
}

void Map::GenerateCastle(D3DXVECTOR2 p)
{
	nbrV->push_back(new Bricks(p.x, p.y, 2, 0));
	nbrV->push_back(new Bricks(p.x+1, p.y, 2, 0));
	nbrV->push_back(new Bricks(p.x, p.y+1, 2, 0));
	nbrV->push_back(new Bricks(p.x+1, p.y+1, 2, 0));
	nbrV->push_back(new Bricks(p.x + 2, p.y + 1, 12, 1));
	nbrV->push_back(new Bricks(p.x + 2, p.y, 13, 1));
	nbrV->push_back(new Bricks(p.x + 3, p.y, 2, 0));
	nbrV->push_back(new Bricks(p.x + 4, p.y, 2, 0));
	nbrV->push_back(new Bricks(p.x + 3, p.y+1, 2, 0));
	nbrV->push_back(new Bricks(p.x + 4, p.y+1, 2, 0));

	nbrV->push_back(new Bricks(p.x, p.y + 2, 11, 0));
	nbrV->push_back(new Bricks(p.x+1, p.y + 2, 11, 1));
	nbrV->push_back(new Bricks(p.x+2, p.y + 2, 11, 1));
	nbrV->push_back(new Bricks(p.x+3, p.y + 2, 11, 1));
	nbrV->push_back(new Bricks(p.x+4, p.y + 2, 11, 0));

	nbrV->push_back(new Bricks(p.x + 1, p.y + 3, 12, 0));
	nbrV->push_back(new Bricks(p.x + 2, p.y + 3, 13, 0));
	nbrV->push_back(new Bricks(p.x + 3, p.y + 3, 14, 0));

	nbrV->push_back(new Bricks(p.x + 1, p.y + 4, 11, 0));
	nbrV->push_back(new Bricks(p.x + 2, p.y + 4, 11, 0));
	nbrV->push_back(new Bricks(p.x + 3, p.y + 4, 11, 0));
}

void Map::GenerateCloud(D3DXVECTOR2 p, int l)
{
	nbrV->push_back(new Bricks(p.x, p.y + 1, 0, 20));
	nbrV->push_back(new Bricks(p.x, p.y, 0, 21));
	for (int i = 0; i < l; i++) {
		nbrV->push_back(new Bricks(p.x+i+1, p.y + 1, 1, 20));
		nbrV->push_back(new Bricks(p.x+i+1, p.y, 1, 21));
	}
	nbrV->push_back(new Bricks(p.x+l+1, p.y + 1, 2, 20));
	nbrV->push_back(new Bricks(p.x+l+1, p.y, 2, 21));
}
