#pragma once
#include "IBreakable.h"
#include "Extra/IBoxItem.h"

class ItemBox : public IBreakable{
public:
	ItemBox(float posx, float posy, float indexx, float indexy);
	virtual ~ItemBox();

	virtual void Bump(int force) override;

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;

	virtual void OnDisposal(vector<Particle*>* pVector) override;
protected:
	void Bounce(float initial, float hooke);

private:
	// Item Inside?
	bool isBouncy;
	float origin;
	float velocity;
	float acceleration;

	vector<IBoxItem*> itemInside;
};