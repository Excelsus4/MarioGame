#include "stdafx.h"
#include "Bricks.h"

Bricks::Bricks(float posx, float posy, float indexx, float indexy)
{
	sprite = new Sprite(Textures + L"Mario/Tiles.png", Shaders + L"008_Sprite.fx", indexx * 16, indexy * 16, (indexx + 1) * 16, (indexy + 1) * 16);
	position = D3DXVECTOR2(posx*16+8, posy*16);
	sprite->Position(position);
}

Bricks::Bricks(D3DXVECTOR2 pos, D3DXVECTOR2 index)
{
	sprite = new Sprite(Textures + L"Mario/Tiles.png", Shaders + L"008_Sprite.fx", index.x * 16, index.y * 16, (index.x + 1) * 16, (index.y + 1) * 16);
	position = pos;
	sprite->Position(pos);
}

Bricks::~Bricks()
{
	SAFE_DELETE(sprite);
}

void Bricks::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	sprite->Update(V, P);
}

void Bricks::Render()
{
	sprite->Render();
}

void Bricks::Position(D3DXVECTOR2 vec)
{
	position = vec;
	sprite->Position(vec);
}
