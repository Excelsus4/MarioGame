#include "stdafx.h"
#include "Item.h"

Item::Item(D3DXVECTOR2 pos):
	IGravity(150.0f)
{
	Position(pos);
}

Item::~Item()
{
}

void Item::Update(D3DXMATRIX & V, D3DXMATRIX & P, World * world)
{
	IGravity::Update(world);
	animation.Update(V, P);
}

void Item::Render()
{
	animation.Render();
}

void Item::Interact_Up(IMario * target)
{
	target->Grow(2);
	isTrash = true;
}

void Item::Interact_Side(IMario * target)
{
	target->Grow(2);
	isTrash = true;
}

void Item::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Item::Position(D3DXVECTOR2 vec)
{
	animation.Position(vec);
}

D3DXVECTOR2 Item::Position() const
{
	return animation.Position();
}

D3DXVECTOR2 Item::Size() const
{
	return animation.TextureSize();
}

void Item::OnDisposal(vector<Particle*>* pVector)
{
}

void Item::Activate(D3DXVECTOR2 origin)
{
	//TODO: start from origin
	// rise to +16
	// rise by a certain speed
	// after rise, free the object
}

void Item::InitializeAsMushroom()
{
	Clip* clip;
	//Mushroom
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(CreateItemSprite(1, 1), 0.2f);
		animation.AddClip(clip);
	}
	animation.Play(0);
}

void Item::SetAnimState(State state)
{
}

Sprite * Item::CreateItemSprite(const int & xIndex, const int & yIndex)
{
	const int xSize = 16;
	const int ySize = 16;

	return new Sprite(Textures + L"Mario/enemies.png",
		Shaders + L"009_Sprite.fx",
		xSize*xIndex, ySize*yIndex, xSize*xIndex + xSize, ySize*yIndex + ySize);
}
