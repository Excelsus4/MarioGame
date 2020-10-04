#include "stdafx.h"
#include "Mario.h"

Mario::Mario() :
	IGravity(250.0f),focusOffset(-20, -60), bHeadingLeft(false), jumpStrength(320.0f), marioLevel(1)
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

	//=========================================================================
	// SUPER MARIO
	//=========================================================================
	// Idle
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(CreateSuperMarioSprite(0, 1), 1.0f);
		AddClip(clip);
	}

	// Walk
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(CreateSuperMarioSprite(1, 1), 0.1f);
		clip->AddFrame(CreateSuperMarioSprite(3, 1), 0.1f);
		clip->AddFrame(CreateSuperMarioSprite(2, 1), 0.1f);
		clip->AddFrame(CreateSuperMarioSprite(3, 1), 0.1f);
		AddClip(clip);
	}

	// Jump
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(CreateSuperMarioSprite(5, 1), 1.0f);
		AddClip(clip);
	}

	// Fall
	{
		clip = new Clip(PlayMode::End);
		clip->AddFrame(CreateSuperMarioSprite(5, 1), 1.0f);
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
	Animation::Update(V, P);
}

void Mario::Update(World* world, vector<Interact*>* entities)
{
	IGravity::Update(world);

	D3DXVECTOR2 position = Position();

	// It is the walking Animation
	if (bOnGround && isMoving != 0) {
		SetAnimState(State::Walk);
	}

	// It is the sideward moving action
	if (isMoving != 0) {
		position.x += speed * Timer->Elapsed() * isMoving;

		//Check with each bricks and find if its wall
		float CPV = position.y;
		float CDV = Size().y / 2;

		float CP = position.x;
		float CD = Size().x / 2;

		for (auto a : *world->bricks) {
			if (a->isAlive) {
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
		}

		for (auto p : *world->platformBricks) {
			if (p->isAlive) {
				float BPV = p->Position().y;
				float BDV = p->TextureSize().y / 2;

				if (CPV + CDV > BPV - BDV && CPV - CDV < BPV + BDV) {
					float BP = p->Position().x;
					float BD = p->TextureSize().x / 2;

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
		}
	}

	if (velocity.y > 0) {
		//Check with each bricks and find if its ceiling
		float CP = position.x;
		float CD = Size().x / 2;

		float CPV = position.y;
		float CDV = Size().y / 2;
		for (auto a : *world->platformBricks) {
			if (a->isAlive) {
				float BP = a->Position().x;
				float BD = a->TextureSize().x / 2;
				if (CP + CD > BP - BD && CP - CD < BP + BD) {
					float BPV = a->Position().y;
					float BDV = a->TextureSize().y / 2;
					if (CPV + CDV >= BPV - BDV && CPV - CDV <= BPV + BDV) {
						position.y = BPV - BDV - CDV;
						velocity.y = 0.0f;
						a->Bump(marioLevel);
					}
				}
			}
		}
	}
	Position(position);

	// Check collision with entities
	if (velocity.y < 0 && !bOnGround) {
		// When going down
		float CP = position.x;
		float CD = Size().x / 2;

		float CPV = position.y;
		float CDV = Size().y / 2;
		for (auto e : *entities) {
			if (e->isAlive) {
				float BP = e->Position().x;
				float BD = e->Size().x / 2;
				if (CP + CD > BP - BD && CP - CD < BP + BD) {
					float BPV = e->Position().y;
					float BDV = e->Size().y / 2;
					if (CPV - CDV <= BPV + BDV && CPV + CDV > BPV - BDV) {
						e->Interact_Up(this);
					}
				}
			}
		}
	}
	else {
		// Else
		float CP = position.x;
		float CD = Size().x / 2;

		float CPV = position.y;
		float CDV = Size().y / 2;
		for (auto e : *entities) {
			if (e->isAlive) {
				float BP = e->Position().x;
				float BD = e->Size().x / 2;
				if (CP + CD > BP - BD && CP - CD < BP + BD) {
					float BPV = e->Position().y;
					float BDV = e->Size().y / 2;
					if (CPV - CDV <= BPV + BDV && CPV + CDV > BPV - BDV) {
						e->Interact_Side(this);
					}
				}
			}
		}
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
		velocity.y = jumpStrength;
		bOnGround = false;
	}
}

void Mario::EndJump()
{
	if (bOnGround == false) {
		UpdateMarioState(State::Fall);
	}
	if (velocity.y > jumpStrength / 3)
		velocity.y = jumpStrength / 3;
}

void Mario::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{
	*position = Animation::Position();

	*size = TextureSize();
}

void Mario::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Mario::Position(D3DXVECTOR2 vec)
{
	Animation::Position(vec);
}

D3DXVECTOR2 Mario::Position() const
{
	return Animation::Position();
}

D3DXVECTOR2 Mario::Size() const
{
	return Animation::TextureSize();
}

void Mario::Damage(int damage)
{
	//TODO: Damage
	if (marioLevel <= 1) {
		//DIE!

	}
	else {
		//LEVEL DOWN! and give a few second invincibility

	}
}

void Mario::Grow(int level)
{
	if (marioLevel < level) {
		UpdateMarioState(level);
		if (level == 2)
			Position(Position() + D3DXVECTOR2(0, 16));
	}
}

void Mario::Bounce(int power)
{
	velocity.y = power;
}

void Mario::SetAnimState(State state)
{
	UpdateMarioState(state);
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
		Play((UINT)marioState+(marioLevel-1)*4);
		RotationDegree(0, 180 * bHeadingLeft, 0);
	}
}

void Mario::UpdateMarioState(State newState)
{
	if (newState == marioState)
		return;
	else {
		marioState = newState;
		Play((UINT)marioState + (marioLevel - 1) * 4);
		RotationDegree(0, 180 * bHeadingLeft, 0);
	}
}

void Mario::UpdateMarioState(int newLevel)
{
	if (newLevel == marioLevel)
		return;
	else {
		marioLevel = newLevel;
		Play((UINT)marioState + (marioLevel - 1) * 4);
		RotationDegree(0, 180 * bHeadingLeft, 0);
	}
}
