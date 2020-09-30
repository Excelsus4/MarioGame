#pragma once
#include "IEntity.h"

class Item : public IEntity {
public:
	Item();
	virtual ~Item();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;

	virtual void Interact_Up() override;
	virtual void Interact_Left() override;
	virtual void Interact_Right() override;

	virtual D3DXVECTOR2 Position() override;
	virtual D3DXVECTOR2 Size() override;

private:


};