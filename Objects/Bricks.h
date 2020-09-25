#pragma once

class Bricks {
public:
	Bricks(D3DXVECTOR2 pos, D3DXVECTOR2 index);
	virtual ~Bricks();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	D3DXVECTOR2 Position() const { return position; }

	D3DXVECTOR2 TextureSize() const { return sprite->TextureSize(); }

private:
	Sprite* sprite;
	D3DXVECTOR2 position;
};