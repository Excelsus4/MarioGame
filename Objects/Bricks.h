#pragma once

class Bricks {
public:
	Bricks(float posx, float posy, float indexx, float indexy);
	Bricks(D3DXVECTOR2 pos, D3DXVECTOR2 index);
	virtual ~Bricks();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	virtual void Render();

	D3DXVECTOR2 Position() const { return position; }

	D3DXVECTOR2 TextureSize() const { return sprite->TextureSize(); }

private:
	Sprite* sprite;
	D3DXVECTOR2 position;
};