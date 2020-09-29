#pragma once
#include "Bricks.h"
#include "DBricks.h"
#include "ItemBox.h"

class Map {
public:
	Map(vector<Bricks*>* brV, vector<Bricks*>* fbrV, vector<Bricks*>* nbrV, vector<IBreakable*>* pbrV);
	virtual ~Map();

	void GenerateMap();
private:
	void GenerateGround(D3DXVECTOR2 p, int l);

	void GeneratePipe(D3DXVECTOR2 p, int h);
	void GenerateBush(D3DXVECTOR2 p, int l);
	void GenerateHedge(D3DXVECTOR2 p, int h);

	void GenerateBrick(D3DXVECTOR2 p);
	void GenerateBrick(D3DXVECTOR2 p, int l);
	void GenerateBox(D3DXVECTOR2 p);

	void GenerateStair(D3DXVECTOR2 p, D3DXVECTOR2 stride, int l);
	void GenerateStairFill(D3DXVECTOR2 p, D3DXVECTOR2 stride, int l);

	void GenerateFlag(D3DXVECTOR2 p);
	void GenerateCastle(D3DXVECTOR2 p);

	void GenerateCloud(D3DXVECTOR2 p, int l);
private:
	vector<Bricks*>* brV;
	vector<Bricks*>* fbrV; 
	vector<Bricks*>* nbrV;
	vector<IBreakable*>* pbrV;
};