#include "stdafx.h"
#include "./Systems/Device.h"
#include "./Objects/Background.h"
#include "./Objects/Mario.h"
#include "./Objects/Bricks.h"

Background* bg;
Mario* animation;
vector<Bricks*> bricks;

void InitScene() {
	bg = new Background(Shaders+L"008_Sprite.fx");

	animation = new Mario();

	animation->Position(100, 170);
	animation->Play(0);

	for(int i = 0; i < 4; i++)
		bricks.push_back(new Bricks(D3DXVECTOR2(250+i*16, 250)));
}

void DestroyScene(){
	SAFE_DELETE(animation);
	SAFE_DELETE(bg);
}

D3DXMATRIX V, P;

void Update() {
	if (Key->Down(VK_RIGHT))
		animation->StartMoving(1);
	else if (Key->Down(VK_LEFT))
		animation->StartMoving(-1);
	else if (Key->Up(VK_RIGHT) && !Key->Press(VK_LEFT))
		animation->StopMoving();
	else if (Key->Up(VK_LEFT) && !Key->Press(VK_RIGHT))
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
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	bg->Update(V, P);
	animation->Update(V, P);
	for (auto a : bricks)
		a->Update(V, P);
}

void Render() {
	D3DXCOLOR bgColor = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		bg->Render();
		for (auto a : bricks)
			a->Render();
		animation->Render();
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}