#include "stdafx.h"
#include "Bricks.h"

Bricks::Bricks(D3DXVECTOR2 pos)
{
	sprite = new Sprite(Textures + L"Mario/Brick.png", Shaders + L"008_Sprite.fx", 272, 112, 288, 128);
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
