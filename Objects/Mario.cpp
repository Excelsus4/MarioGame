#include "stdafx.h"
#include "Mario.h"

Mario::Mario():
speed(250.0f), velocity(0.0f), gravity(-600), 
bOnGround(false), bHeadingLeft(false), jumpStrength(320.0f)
{
	Clip* clip;
	// Idle
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(CreateMarioSprite(0, 0), 1.0f);
		AddClip(clip);
	}

	// Walk
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(CreateMarioSprite(1, 0), 0.1f);
		clip->AddFrame(CreateMarioSprite(3, 0), 0.1f);
		clip->AddFrame(CreateMarioSprite(2, 0), 0.1f);
		clip->AddFrame(CreateMarioSprite(3, 0), 0.1f);
		AddClip(clip);
	}

	// Jump
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(CreateMarioSprite(5, 0), 1.0f);
		AddClip(clip);
	}

	// Fall
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(CreateMarioSprite(5, 0), 1.0f);
		AddClip(clip);
	}

	marioState = State::Idle;
	Play((UINT)marioState);
}

Mario::~Mario()
{
}

void Mario::Update(D3DXMATRIX & V, D3DXMATRIX & P, vector<Bricks*>* brV, vector<Bricks*>* fbrV)
{
	__super::Update(V, P);
	D3DXVECTOR2 position = Position();
	velocity += gravity * Timer->Elapsed();

	// Gravity 
	if (bOnGround == false) {
		if(marioState != State::Jump)
			UpdateMarioState(State::Fall);
		position.y += velocity * Timer->Elapsed();
		Position(position);
	}
	else if(position.y > TextureSize().y*0.5f + 105){
		// Check if ground is still there
		float CP = position.x;
		float CD = TextureSize().x / 2;

		bool isGroundExist = false;
		for (auto a : *brV) {
			float BP = a->Position().x;
			float BD = a->TextureSize().x / 2;
			if (CP + CD > BP - BD && CP - CD < BP + BD) {
				isGroundExist = true;
				break;
			}
		}
		if (!isGroundExist) {
			for (auto fb : *fbrV) {
				float BP = fb->Position().x;
				float BD = fb->TextureSize().x / 2;
				if (CP + CD > BP - BD && CP - CD < BP + BD) {
					isGroundExist = true;
					break;
				}
			}
		}
		if (!isGroundExist) {
			UpdateMarioState(State::Fall);
			bOnGround = false;
		}
	}

	// The Bedrock floor
	if (position.y <= TextureSize().y*0.5f+0) {
		if(marioState != State::Walk)
			UpdateMarioState(State::Idle);
		position.y = TextureSize().y*0.5f+50;
		velocity = 0.0f;

		//bOnGround = true;

		Position(position);
	}
	else if(velocity<0) {
		//Check with each bricks and find if its floor
		float CP = position.x;
		float CD = TextureSize().x / 2;

		float CPV = position.y;
		float CDV = TextureSize().y / 2;

		for (auto a : *brV) {
			float BP = a->Position().x;
			float BD = a->TextureSize().x / 2;
			if (CP + CD > BP - BD && CP - CD < BP + BD) {
				float BPV = a->Position().y;
				float BDV = a->TextureSize().y / 2;

				if (CPV - CDV <= BPV + BDV && CPV+CDV>BPV-BDV) {
					if (marioState != State::Walk)
						UpdateMarioState(State::Idle);
					position.y = BPV + BDV + CDV;
					velocity = 0.0f;
					bOnGround = true;
					Position(position);
					break;
				}
			}
		}
		if (!bOnGround) {
			for (auto fb : *fbrV) {
				float BP = fb->Position().x;
				float BD = fb->TextureSize().x / 2;
				if (CP + CD > BP - BD && CP - CD < BP + BD) {
					float BPV = fb->Position().y;
					float BDV = fb->TextureSize().y / 2;

					if (CPV - CDV <= BPV + BDV && CPV + CDV > BPV - BDV) {
						if (marioState != State::Walk)
							UpdateMarioState(State::Idle);
						position.y = BPV + BDV + CDV;
						velocity = 0.0f;
						bOnGround = true;
						Position(position);
						break;
					}
				}
			}
		}
	}
	else if (velocity > 0) {
		//Check with each bricks and find if its ceiling
		float CP = position.x;
		float CD = TextureSize().x / 2;

		float CPV = position.y;
		float CDV = TextureSize().y / 2;
		for (auto a : *brV) {
			float BP = a->Position().x;
			float BD = a->TextureSize().x / 2;
			if (CP + CD > BP - BD && CP - CD < BP + BD) {
				float BPV = a->Position().y;
				float BDV = a->TextureSize().y / 2;
				if (CPV + CDV >= BPV - BDV && CPV - CDV <= BPV + BDV) {
					position.y = BPV - BDV - CDV;
					velocity = 0.0f;
					Position(position);
					break;
				}
			}
		}
	}

	// It is the walking Animation
	if (bOnGround && isMoving != 0) {

		UpdateMarioState(State::Walk);
	}

	// It is the sideward moving action
	if (isMoving != 0) {
		D3DXVECTOR2 position = Position();
		position.x += speed * Timer->Elapsed() * isMoving;

		//Check with each bricks and find if its wall
		float CPV = position.y;
		float CDV = TextureSize().y / 2;

		float CP = position.x;
		float CD = TextureSize().x / 2;
		
		for (auto a : *brV) {
			float BPV = a->Position().y;
			float BDV = a->TextureSize().y / 2;

			if (CPV + CDV > BPV - BDV && CPV - CDV < BPV + BDV) {
				float BP = a->Position().x;
				float BD = a->TextureSize().x / 2;

				if (CP + CD > BP - BD && CP - CD < BP + BD) {
					if (CP > BP) {
						position.x = BP + BD + CD;
					}
					else {
						position.x = BP - BD - CD;
					}
				}
			}
		}

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
	const int xSize = 16;
	const int ySize = 16;

	return new Sprite(Textures + L"Mario/mario_custom.png",
		Shaders + L"009_Sprite.fx",
		xSize*xIndex, ySize*yIndex, xSize*xIndex + xSize, ySize*yIndex + ySize);
}

Sprite * Mario::CreateSuperMarioSprite(const int & xIndex, const int & yIndex)
{
	const int xSize = 16;
	const int ySize = 32;

	return new Sprite(Textures + L"Mario/mario_custom.png",
		Shaders + L"009_Sprite.fx",
		xSize*xIndex, ySize*yIndex + 16, xSize*xIndex + xSize, ySize*yIndex + ySize + 16);
}

void Mario::UpdateMarioState(bool headLeft)
{
	if (headLeft == bHeadingLeft)
		return;
	else {
		bHeadingLeft = headLeft;
		Play((UINT)marioState);
		RotationDegree(0, 180 * bHeadingLeft, 0);
	}
}

void Mario::UpdateMarioState(State newState)
{
	if (newState == marioState)
		return;
	else {
		marioState = newState;
		Play((UINT)marioState);
		RotationDegree(0, 180 * bHeadingLeft, 0);
	}
}
