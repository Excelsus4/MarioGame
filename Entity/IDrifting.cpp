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

	// �� üũ�ϰ� ���� ������ �ݴ�������� ������
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
					// ���⿡ ���� ���⼺ ������.. ����!
					velocity.x = -velocity.x;
				}
				else {
					position.x = BP - BD - CD;
					// ���⿡ ���� ���⼺ ������.. ����!
					velocity.x = -velocity.x;
				}
			}
		}
	}

	Position(position);
}
