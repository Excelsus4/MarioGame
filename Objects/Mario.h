#pragma once
#include "Objects/Bricks.h"
#include "Viewer/IFollowing.h"

enum class State {
	Idle = 0, Walk, Jump, Fall
};

class Mario :public Animation, public IFollowing {
public:
	Mario();
	virtual ~Mario();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P, vector<Bricks*>* brV, vector<Bricks*>* fbrV);

	void StartMoving(int Direction);
	void StopMoving();

	void StartJump();
	void EndJump();

	virtual void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size) override;
	
private:
	Sprite* CreateMarioSprite(const int& xIndex, const int& yIndex);
	Sprite* CreateSuperMarioSprite(const int& xIndex, const int& yIndex);
	void UpdateMarioState(bool headLeft);
	void UpdateMarioState(State newState);

private:
	State marioState;
	bool bHeadingLeft;

	float speed;
	float gravity;
	float jumpStrength;

	float velocity;
	bool bOnGround;
	int isMoving;

	D3DXVECTOR2 focusOffset;
};