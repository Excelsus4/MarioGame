#include "stdafx.h"
#include "DBricks.h"

DBricks::DBricks(float posx, float posy, float indexx, float indexy):
	IBreakable(posx, posy, indexx, indexy), isBouncy(false)
{

}

DBricks::~DBricks()
{

}

void DBricks::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (isBouncy) {
		D3DXVECTOR2 pos = Position();
		velocity += acceleration * Timer->Elapsed();
		pos.y += velocity * Timer->Elapsed();
		if (pos.y <= origin) {
 			pos.y = origin;
			isBouncy = false;
		}
		Position(pos);
	}

	__super::Update(V, P);
}

void DBricks::Bump(int force)
{
	if (force > 1) {
		//TOTAL DESTRUCTION
		isTrash = true;
	}
	else if (force == 1) {
		//That small bounce.
		Bounce(160.0f, -1280.0f);
	}
}

void DBricks::OnDisposal(vector<Particle*>* pVector)
{
	//Create breaking brick particles flying around
	{
		Animation* anim = new Animation();
		Clip* clip = new Clip(PlayMode::Loop);
		clip->AddFrame(CreateBrickDebris(0, 0), 0.1f);
		clip->AddFrame(CreateBrickDebris(0, 1), 0.1f);
		clip->AddFrame(CreateBrickDebris(1, 1), 0.1f);
		clip->AddFrame(CreateBrickDebris(1, 0), 0.1f);
		anim->AddClip(clip);
		anim->Position(Position() + D3DXVECTOR2(-4, 4));
		pVector->push_back(new Particle(anim, 500, D3DXVECTOR2(-50, 250), 2));
	}
	{
		Animation* anim = new Animation();
		Clip* clip = new Clip(PlayMode::Loop);
		clip->AddFrame(CreateBrickDebris(0, 1), 0.1f);
		clip->AddFrame(CreateBrickDebris(1, 1), 0.1f);
		clip->AddFrame(CreateBrickDebris(1, 0), 0.1f);
		clip->AddFrame(CreateBrickDebris(0, 0), 0.1f);
		anim->AddClip(clip);
		anim->Position(Position() + D3DXVECTOR2(-4, -4));
		pVector->push_back(new Particle(anim, 500, D3DXVECTOR2(-50, 200), 2));
	}
	{
		Animation* anim = new Animation();
		Clip* clip = new Clip(PlayMode::Loop);
		clip->AddFrame(CreateBrickDebris(1, 1), 0.1f);
		clip->AddFrame(CreateBrickDebris(1, 0), 0.1f);
		clip->AddFrame(CreateBrickDebris(0, 0), 0.1f);
		clip->AddFrame(CreateBrickDebris(0, 1), 0.1f);
		anim->AddClip(clip);
		anim->Position(Position() + D3DXVECTOR2(4, -4));
		pVector->push_back(new Particle(anim, 500, D3DXVECTOR2(50, 200), 2));
	}
	{
		Animation* anim = new Animation();
		Clip* clip = new Clip(PlayMode::Loop);
		clip->AddFrame(CreateBrickDebris(1, 0), 0.1f);
		clip->AddFrame(CreateBrickDebris(0, 0), 0.1f);
		clip->AddFrame(CreateBrickDebris(0, 1), 0.1f);
		clip->AddFrame(CreateBrickDebris(1, 1), 0.1f);
		anim->AddClip(clip);
		anim->Position(Position() + D3DXVECTOR2(4, 4));
		pVector->push_back(new Particle(anim, 500, D3DXVECTOR2(50, 250), 2));
	}


}

void DBricks::Bounce(float initial, float hooke)
{
	velocity = initial;
	acceleration = hooke;
	isBouncy = true;
	origin = Position().y;
}

Sprite * DBricks::CreateBrickDebris(const int & xIndex, const int & yIndex)
{
	const int xSize = 8;
	const int ySize = 8;

	return new Sprite(Textures + L"Mario/Tiles.png",
		Shaders + L"008_Sprite.fx",
		432 + xSize * xIndex, 0 + ySize * yIndex, 440 + xSize * xIndex, 8 + ySize * yIndex);
}
