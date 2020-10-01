#pragma once
#include "IGravity.h"
#include "Objects/Bricks.h"
#include "Objects/IBreakable.h"
#include "Viewer/IFollowing.h"
#include "Interact.h"

class Mario : public IGravity, public Animation, public IFollowing, public IMario {
public:
	Mario();
	virtual ~Mario();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P, World* world, vector<Interact*>* entities);

	void StartMoving(int Direction);
	void StopMoving();

	void StartJump();
	void EndJump();

	virtual void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size) override;

	virtual void Position(float x, float y);
	virtual void Position(D3DXVECTOR2 vec);
	virtual D3DXVECTOR2 Position() const;

	virtual D3DXVECTOR2 Size() const;

	virtual void Damage(int damage) override;
	virtual void Grow(int level) override;
	virtual void Bounce(int power) override;

protected:
	virtual void SetAnimState(State state) override;
	
private:
	Sprite* CreateMarioSprite(const int& xIndex, const int& yIndex);
	Sprite* CreateSuperMarioSprite(const int& xIndex, const int& yIndex);
	void UpdateMarioState(bool headLeft);
	void UpdateMarioState(State newState);

private:
	int marioLevel;
	State marioState;
	bool bHeadingLeft;

	float jumpStrength;

	D3DXVECTOR2 focusOffset;
};