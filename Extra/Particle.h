#pragma once

class Particle {
public:
	Particle(Animation* anim, float gravity, D3DXVECTOR2 velocity, float ttl);
	virtual ~Particle();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

public:
	bool isTrash;
private:
	Animation* animation;

	float gravity;
	D3DXVECTOR2 velocity;

	float ttl;
	float age;
};