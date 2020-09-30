#pragma once
#include "IGravity.h"
#include "Interact.h"

class Goomba : public IGravity, public Interact{
public:
	Goomba(D3DXVECTOR2 pos);
	virtual ~Goomba();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P, World* world) override;
	virtual void Render() override;

	virtual void Interact_Up(IMario* target) override;
	virtual void Interact_Left(IMario* target) override;
	virtual void Interact_Right(IMario* target) override;

	virtual void Position(float x, float y) override;
	virtual void Position(D3DXVECTOR2 vec) override;
	virtual D3DXVECTOR2 Position() const override;

	virtual D3DXVECTOR2 Size() const override;

protected:
	virtual void SetAnimState(State state) override;

private:
	Sprite* CreateGoombaSprite(const int& xIndex, const int& yIndex);

private:
	Animation animation;
};