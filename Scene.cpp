#include "stdafx.h"
#include "./Systems/Device.h"
#include "./Objects/Mario.h"
#include "./Objects/Bricks.h"
#include "./Objects/Map.h"
#include "./Viewer/Following.h"

Camera* camera;

Mario* animation;
vector<Bricks*> bricks;
vector<Bricks*> floorOnlyBricks;
vector<Bricks*> nonPhysicBricks;
vector<IBreakable*> platformBricks;

void InitScene() {
	animation = new Mario();

	animation->Position(100, 170);
	animation->Play(0);

	camera = new Following(animation);

	Map map(&bricks, &floorOnlyBricks, &nonPhysicBricks, &platformBricks);
	map.GenerateMap();
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

	//Projection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width / WindowScale.x, 0, (float)Height / WindowScale.y, -1, 1);

	//View
	camera->Update();

	D3DXMATRIX V = camera->View();

	//Update
	animation->Update(V, P, &bricks, &floorOnlyBricks, &platformBricks);
	for (auto a : bricks)
		a->Update(V, P);
	for (auto fb : floorOnlyBricks)
		fb->Update(V, P);
	for (auto nb : nonPhysicBricks)
		nb->Update(V, P);
	for (auto p : platformBricks)
		p->Update(V, P);
}

void Render() {
	D3DXCOLOR bgColor = D3DXCOLOR(0.36f, 0.58f, 0.99f, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		for (auto nb : nonPhysicBricks)
			nb->Render();
		for (auto fb : floorOnlyBricks)
			fb->Render();
		for (auto a : bricks)
			a->Render();
		for (auto p : platformBricks)
			p->Render();
		animation->Render();
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}