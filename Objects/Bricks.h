#pragma once
#include "Viewer/IViewDrivenLife.h"

class Bricks :public IViewDrivenLife{
public:
	Bricks(float posx, float posy, float indexx, float indexy);
	Bricks(D3DXVECTOR2 pos, D3DXVECTOR2 index);
	virtual ~Bricks();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	virtual void Render();

	virtual D3DXVECTOR2 Position() const override { return position; }
	virtual D3DXVECTOR2 Size() const override { return TextureSize(); }
	D3DXVECTOR2 TextureSize() const { return sprite->TextureSize(); }

private:
	Sprite* sprite;
	D3DXVECTOR2 position;
};