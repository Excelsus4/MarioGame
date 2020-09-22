#pragma once

class Bricks {
public:
	Bricks(D3DXVECTOR2 pos);
	virtual ~Bricks();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

private:
	Sprite* sprite;
	D3DXVECTOR2 position;
};