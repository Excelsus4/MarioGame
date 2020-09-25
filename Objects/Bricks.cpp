#include "stdafx.h"
#include "Bricks.h"

Bricks::Bricks(D3DXVECTOR2 pos, D3DXVECTOR2 index)
{
	sprite = new Sprite(Textures + L"Mario/custom.png", Shaders + L"008_Sprite.fx", index.x * 16, index.y * 16, (index.x + 1) * 16, (index.y + 1) * 16);
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
