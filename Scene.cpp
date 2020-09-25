#include "stdafx.h"
#include "./Systems/Device.h"
#include "./Objects/Mario.h"
#include "./Objects/Bricks.h"
#include "./Objects/Map.h"

Mario* animation;
vector<Bricks*> bricks;
vector<Bricks*> floorOnlyBricks;
vector<Bricks*> nonPhysicBricks;

void InitScene() {
	animation = new Mario();

	animation->Position(100, 170);
	animation->Play(0);

	Map::MapGen(&bricks, &floorOnlyBricks, &nonPhysicBricks);
}

void DestroyScene(){
	SAFE_DELETE(animation);
	for (auto b : bricks)
		SAFE_DELETE(b);
	for (auto fb : floorOnlyBricks)
		SAFE_DELETE(fb);
	for (auto nb : nonPhysicBricks)
		SAFE_DELETE(nb);
}

D3DXMATRIX V, P;

void Update() {
	if (Key->Down(VK_RIGHT))
		animation->StartMoving(1);
	else if (Key->Down(VK_LEFT))
		animation->StartMoving(-1);
	else if (Key->Up(VK_RIGHT) && !Key->Press(VK_LEFT)||
			 Key->Up(VK_LEFT) && !Key->Press(VK_RIGHT))
		animation->StopMoving();

	if (Key->Down(VK_SPACE))
		animation->StartJump();
	else if (Key->Up(VK_SPACE))
		animation->EndJump();

	//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Projection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width/2, 0, (float)Height/2, -1, 1);

	animation->Update(V, P, &bricks, &floorOnlyBricks);
	for (auto a : bricks)
		a->Update(V, P);
	for (auto fb : floorOnlyBricks)
		fb->Update(V, P);
	for (auto nb : nonPhysicBricks)
		nb->Update(V, P);
}

void Render() {
	D3DXCOLOR bgColor = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		for (auto a : bricks)
			a->Render();
		for (auto fb : floorOnlyBricks)
			fb->Render();
		for (auto nb : nonPhysicBricks)
			nb->Render();
		animation->Render();
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}