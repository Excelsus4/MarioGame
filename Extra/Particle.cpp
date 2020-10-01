#include "stdafx.h"
#include "Particle.h"

Particle::Particle(Animation * anim, float gravity, D3DXVECTOR2 velocity, float ttl):
	animation(anim), gravity(gravity), velocity(velocity),
	isTrash(false), ttl(ttl), age(0)
{
	animation->Play(0);
}

Particle::~Particle()
{
	SAFE_DELETE(animation);
}

void Particle::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	age += Timer->Elapsed();
	if (age > ttl)
		isTrash = true;
	animation->Update(V, P);
}

void Particle::Render()
{
	animation->Render();
}
