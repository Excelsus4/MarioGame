#pragma once
#include "IGravity.h"
#include "Interact.h"
#include "Extra/IBoxItem.h"

class Item : public IGravity, public Interact, public IBoxItem {
public:
	Item(D3DXVECTOR2 pos);
	virtual ~Item();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P, World* world) override;
	virtual void Render() override;

	virtual void Interact_Up(IMario* target) override;
	virtual void Interact_Side(IMario* target) override;

	virtual void Position(float x, float y) override;
	virtual void Position(D3DXVECTOR2 vec) override;
	virtual D3DXVECTOR2 Position() const override;

	virtual D3DXVECTOR2 Size() const override;

	virtual void OnDisposal(vector<Particle*>* pVector) override;

	virtual void Activate(D3DXVECTOR2 origin) override;

	void InitializeAsMushroom();
protected:
	virtual void SetAnimState(State state) override;
	Sprite* CreateItemSprite(const int& xIndex, const int& yIndex);

private:
	Animation animation;
};