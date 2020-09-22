#include "stdafx.h"
#include "Mario.h"

Mario::Mario():
speed(250.0f), velocity(0.0f), gravity(-1.5f), 
bOnGround(false), bHeadingLeft(false), jumpStrength(0.6f)
{
	Clip* clip;
	// Idle
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(CreateMarioSprite(0, 3), 1.0f);
		AddClip(clip);
	}

	// Walk
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(CreateMarioSprite(1, 0), 0.1f);
		clip->AddFrame(CreateMarioSprite(0, 0), 0.1f);
		clip->AddFrame(CreateMarioSprite(1, 0), 0.1f);
		clip->AddFrame(CreateMarioSprite(0, 3), 0.1f);
		AddClip(clip);
	}

	// Jump
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(CreateMarioSprite(2, 0), 1.0f);
		AddClip(clip);
	}

	// Fall
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(CreateMarioSprite(3, 0), 1.0f);
		AddClip(clip);
	}

	//============================================================================
	// Opposite

	// Idle
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(CreateMarioSprite(4, 3), 1.0f);
		AddClip(clip);
	}

	// Walk
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(CreateMarioSprite(5, 0), 0.1f);
		clip->AddFrame(CreateMarioSprite(4, 0), 0.1f);
		clip->AddFrame(CreateMarioSprite(5, 0), 0.1f);
		clip->AddFrame(CreateMarioSprite(4, 3), 0.1f);
		AddClip(clip);
	}

	// Jump
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(CreateMarioSprite(6, 0), 1.0f);
		AddClip(clip);
	}

	// Fall
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(CreateMarioSprite(7, 0), 1.0f);
		AddClip(clip);
	}

	marioState = State::Idle;
	Play((UINT)marioState);
}

Mario::~Mario()
{
}

void Mario::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	__super::Update(V, P);
	D3DXVECTOR2 position = Position();
	velocity += gravity * Timer->Elapsed();

	if (bOnGround == false) {
		if(marioState != State::Jump)
			UpdateMarioState(State::Fall);
		position.y += velocity;
		Position(position);
	}
	if (position.y < TextureSize().y*0.5f+105) {
		if(marioState != State::Walk)
			UpdateMarioState(State::Idle);
		position.y = TextureSize().y*0.5f+105;
		velocity = 0.0f;

		bOnGround = true;

		Position(position);
	}
	if (bOnGround && isMoving != 0) {

		UpdateMarioState(State::Walk);
	}
	if (isMoving != 0) {
		D3DXVECTOR2 position = Position();
		position.x += speed * Timer->Elapsed() * isMoving;
		Position(position);
	}
}

void Mario::StartMoving(int Direction)
{
	if (Direction < 0)
		UpdateMarioState(true);
	else if (Direction > 0)
		UpdateMarioState(false);

	isMoving = Direction;
	if (bOnGround)
		UpdateMarioState(State::Walk);
}

void Mario::StopMoving()
{
	isMoving = 0;
	if(bOnGround)
		UpdateMarioState(State::Idle);
}

void Mario::StartJump()
{
	if (bOnGround == true) {
		UpdateMarioState(State::Jump);
		velocity = jumpStrength;
		bOnGround = false;
	}
}

void Mario::EndJump()
{
	if (bOnGround == false) {
		UpdateMarioState(State::Fall);
	}
	if (velocity > jumpStrength / 3)
		velocity = jumpStrength / 3;
}

Sprite * Mario::CreateMarioSprite(const int & xIndex, const int & yIndex)
{
	const int xSize = 64;
	const int ySize = 82;

	return new Sprite(Textures + L"Mario/All.png",
		Shaders + L"008_Sprite.fx",
		xSize*xIndex, ySize*yIndex, xSize*xIndex + xSize, ySize*yIndex + ySize);
}

void Mario::UpdateMarioState(bool headLeft)
{
	if (headLeft == bHeadingLeft)
		return;
	else {
		bHeadingLeft = headLeft;
		Play((UINT)marioState + 4 * bHeadingLeft);
	}
}

void Mario::UpdateMarioState(State newState)
{
	if (newState == marioState)
		return;
	else {
		marioState = newState;
		Play((UINT)marioState + 4*bHeadingLeft);
	}
}
