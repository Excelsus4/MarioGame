#include "stdafx.h"
#include "Goomba.h"

Goomba::Goomba(D3DXVECTOR2 pos):
	IGravity(150.0f), isFlat(false), IDrifting(D3DXVECTOR2(-40.0f, 0.0f))
{
	Clip* clip;
	//Only Walk Available
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(CreateGoombaSprite(0, 0), 0.2f);
		clip->AddFrame(CreateGoombaSprite(1, 0), 0.2f);
		animation.AddClip(clip);
	}

	// Flatten
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(CreateGoombaSprite(2, 0), 0.2f);
		animation.AddClip(clip);
	}

	animation.Play(0);
	Position(pos);
}

Goomba::~Goomba()
{
}

void Goomba::Update(D3DXMATRIX & V, D3DXMATRIX & P, World* world)
{
	animation.Update(V, P);
	IGravity::Update(world);
	IDrifting::Update(world);
}

void Goomba::Render()
{
	animation.Render();
}

void Goomba::Interact_Up(IMario* target)
{
	target->Bounce(200);
	isFlat = true;
	isTrash = true;
}

void Goomba::Interact_Side(IMario* target)
{
	target->Damage(1);
}

void Goomba::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Goomba::Position(D3DXVECTOR2 vec)
{
	animation.Position(vec);
}

D3DXVECTOR2 Goomba::Position() const
{
	return animation.Position();
}

D3DXVECTOR2 Goomba::Size() const
{
	return animation.TextureSize();
}

void Goomba::OnDisposal(vector<Particle*>* pVector)
{
	if (isFlat) {
		// Goomba is killed by flattening attack
		Animation* anim = new Animation();
		Clip* clip = new Clip(PlayMode::End);
		clip->AddFrame(CreateGoombaSprite(2, 0), 0.2f);
		anim->AddClip(clip);
		anim->Position(Position());
		pVector->push_back(new Particle(anim, 0.0f, D3DXVECTOR2(0, 0), 0.6f));
	}
	else {
		// Goomba is killed by Something else
		//TODO: Create a flying particle
	}
}

void Goomba::SetAnimState(State state)
{
	//DO NOTHING
	//MAYBE FLATTEN?
}

Sprite * Goomba::CreateGoombaSprite(const int & xIndex, const int & yIndex)
{
	const int xSize = 16;
	const int ySize = 16;

	return new Sprite(Textures+L"Mario/enemies.png",
		Shaders+L"009_Sprite.fx",
		xSize*xIndex, ySize*yIndex, xSize*xIndex + xSize, ySize*yIndex + ySize);
}
