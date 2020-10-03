#include "stdafx.h"
#include "IDrifting.h"

IDrifting::IDrifting(D3DXVECTOR2 speed):
	velocity(speed)
{
}

void IDrifting::Update(World * world)
{
	D3DXVECTOR2 position = Position();
	position += velocity * Timer->Elapsed();

	// 벽 체크하고 벽에 닿으면 반대방향으로 뒤집기
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
					// 여기에 이제 방향성 뒤집기.. 으억!
					velocity.x = -velocity.x;
				}
				else {
					position.x = BP - BD - CD;
					// 여기에 이제 방향성 뒤집기.. 으억!
					velocity.x = -velocity.x;
				}
			}
		}
	}

	Position(position);
}
