#include "stdafx.h"
#include "IGravity.h"

IGravity::IGravity(float speed):
	speed(speed), velocity(0.0f), gravity(-600), bOnGround(false)
{
}

IGravity::~IGravity()
{
}

void IGravity::Update(World * world)
{
	D3DXVECTOR2 position = Position();
	velocity += gravity * Timer->Elapsed();

	// Gravity 
	if (bOnGround == false) {
		if (currentState != State::Jump)
			SetAnimState(State::Fall);
		position.y += velocity * Timer->Elapsed();
		Position(position);
	}
	else {
		// Check if ground is still there
		float CP = position.x;
		float CD = Size().x / 2;

		float CPV = position.y;
		float CDV = Size().y / 2;

		bool isGroundExist = false;
		for (auto a : *world->bricks) {
			float BP = a->Position().x;
			float BD = a->TextureSize().x / 2;
			if (CP + CD > BP - BD && CP - CD < BP + BD) {
				float BPV = a->Position().y;
				float BDV = a->TextureSize().y / 2;
				if (CPV - CDV <= BPV + BDV && CPV + CDV > BPV - BDV)
					isGroundExist = true;
				break;
			}
		}
		if (!isGroundExist) {
			for (auto fb : *world->floorOnlyBricks) {
				float BP = fb->Position().x;
				float BD = fb->TextureSize().x / 2;
				if (CP + CD > BP - BD && CP - CD < BP + BD) {
					float BPV = fb->Position().y;
					float BDV = fb->TextureSize().y / 2;
					if (CPV - CDV <= BPV + BDV && CPV + CDV > BPV - BDV)
						isGroundExist = true;
					break;
				}
			}
		}

		if (!isGroundExist) {
			for (auto p : *world->platformBricks) {
				float BP = p->Position().x;
				float BD = p->TextureSize().x / 2;
				if (CP + CD > BP - BD && CP - CD < BP + BD) {
					float BPV = p->Position().y;
					float BDV = p->TextureSize().y / 2;
					if (CPV - CDV <= BPV + BDV && CPV + CDV > BPV - BDV)
						isGroundExist = true;
					break;
				}
			}
		}

		if (!isGroundExist) {
			SetAnimState(State::Fall);
			bOnGround = false;
		}
	}
	// The Bedrock floor
	if (position.y <= Size().y*0.5f + 0) {
		if (currentState != State::Walk)
			SetAnimState(State::Idle);
		position.y = Size().y*0.5f + 50;
		velocity = 0.0f;

		//bOnGround = true;

		Position(position);
	}
	else if (velocity < 0) {
		//Check with each bricks and find if its floor
		float CP = position.x;
		float CD = Size().x / 2;

		float CPV = position.y;
		float CDV = Size().y / 2;

		for (auto a : *world->bricks) {
			float BP = a->Position().x;
			float BD = a->TextureSize().x / 2;
			if (CP + CD > BP - BD && CP - CD < BP + BD) {
				float BPV = a->Position().y;
				float BDV = a->TextureSize().y / 2;

				if (CPV - CDV <= BPV + BDV && CPV + CDV > BPV - BDV) {
					if (currentState != State::Walk)
						SetAnimState(State::Idle);
					position.y = BPV + BDV + CDV;
					velocity = 0.0f;
					bOnGround = true;
					Position(position);
					break;
				}
			}
		}
		if (!bOnGround) {
			for (auto fb : *world->floorOnlyBricks) {
				float BP = fb->Position().x;
				float BD = fb->TextureSize().x / 2;
				if (CP + CD > BP - BD && CP - CD < BP + BD) {
					float BPV = fb->Position().y;
					float BDV = fb->TextureSize().y / 2;

					if (CPV - CDV <= BPV + BDV && CPV + CDV > BPV - BDV) {
						if (currentState != State::Walk)
							SetAnimState(State::Idle);
						position.y = BPV + BDV + CDV;
						velocity = 0.0f;
						bOnGround = true;
						Position(position);
						break;
					}
				}
			}
		}
		if (!bOnGround) {
			for (auto p : *world->platformBricks) {
				float BP = p->Position().x;
				float BD = p->TextureSize().x / 2;
				if (CP + CD > BP - BD && CP - CD < BP + BD) {
					float BPV = p->Position().y;
					float BDV = p->TextureSize().y / 2;

					if (CPV - CDV <= BPV + BDV && CPV + CDV > BPV - BDV) {
						if (currentState != State::Walk)
							SetAnimState(State::Idle);
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


	// It is the walking Animation
	if (bOnGround && isMoving != 0) {
		SetAnimState(State::Walk);
	}

	// It is the sideward moving action
	if (isMoving != 0) {
		D3DXVECTOR2 position = Position();
		position.x += speed * Timer->Elapsed() * isMoving;

		//Check with each bricks and find if its wall
		float CPV = position.y;
		float CDV = Size().y / 2;

		float CP = position.x;
		float CD = Size().x / 2;

		for (auto a : *world->bricks) {
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

		for (auto p : *world->platformBricks) {
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

		Position(position);
	}
}