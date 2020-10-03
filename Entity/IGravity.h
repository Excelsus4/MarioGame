#pragma once
#include "Objects/Bricks.h"
#include "Objects/IBreakable.h"

struct World {
	vector<Bricks*>* bricks;
	vector<Bricks*>* floorOnlyBricks;
	vector<Bricks*>* nonPhysicBricks;
	vector<IBreakable*>* platformBricks;
};

enum class State {
	Idle = 0, Walk, Jump, Fall
};

class IGravity {
public:
	IGravity(float speed);
	virtual ~IGravity();

	virtual void Update(World* world);

	virtual void Position(float x, float y) = 0;
	virtual void Position(D3DXVECTOR2 vec) = 0;
	virtual D3DXVECTOR2 Position() const = 0;

	virtual D3DXVECTOR2 Size() const = 0;

protected:
	virtual void SetAnimState(State state) = 0;

protected:
	float gravity;
	D3DXVECTOR2 velocity;
	bool bOnGround;
	int isMoving;
	float speed;

	State currentState;
};