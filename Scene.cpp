#include "stdafx.h"
#include "./Systems/Device.h"
#include "./Entity/Mario.h"
#include "./Objects/Bricks.h"
#include "./Objects/Map.h"
#include "./Viewer/Following.h"
#include "./Entity/Interact.h"
#include "./Entity/Goomba.h"

Camera* camera;

Mario* animation;
vector<Bricks*> bricks;
vector<Bricks*> floorOnlyBricks;
vector<Bricks*> nonPhysicBricks;
vector<IBreakable*> platformBricks;
vector<Interact*> Entities;
vector<Particle*> particles;

World world;

void InitScene() {
	animation = new Mario();

	animation->Position(100, 170);
	animation->Play(0);

	camera = new Following(animation);

	Map map(&bricks, &floorOnlyBricks, &nonPhysicBricks, &platformBricks);
	map.GenerateMap();

	world.bricks = &bricks;
	world.floorOnlyBricks = &floorOnlyBricks;
	world.nonPhysicBricks = &nonPhysicBricks;
	world.platformBricks = &platformBricks;

	Entities.push_back(new Goomba(D3DXVECTOR2(250, 170)));
}

void DestroyScene(){
	SAFE_DELETE(animation);
	for (auto b : bricks)
		SAFE_DELETE(b);
	for (auto fb : floorOnlyBricks)
		SAFE_DELETE(fb);
	for (auto nb : nonPhysicBricks)
		SAFE_DELETE(nb);
	for (auto ee : Entities)
		SAFE_DELETE(ee);
	for (auto p : particles)
		SAFE_DELETE(p);
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
	animation->Update(V, P, &world, &Entities);
	for (auto a : bricks)
		a->Update(V, P);
	for (auto fb : floorOnlyBricks)
		fb->Update(V, P);
	for (auto nb : nonPhysicBricks)
		nb->Update(V, P);
	for (auto p : platformBricks)
		p->Update(V, P);
	for (auto ee : Entities)
		ee->Update(V, P, &world);

	// DISPOSAL CODE
	for (auto iter = Entities.begin(); iter != Entities.end();) {
		if ((*iter)->isTrash) {
			(*iter)->OnDisposal(&particles);
			SAFE_DELETE(*iter);
			iter = Entities.erase(iter);
		}
		else {
			iter++;
		}
	}

	// PARTICLE DISPOSAL
	for (auto iter = particles.begin(); iter != particles.end();) {
		if ((*iter)->isTrash) {
			SAFE_DELETE(*iter);
			iter = particles.erase(iter);
		}
		else {
			iter++;
		}
	}



	for (auto p : particles)
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
		for (auto ee : Entities)
			ee->Render();

		animation->Render();

		for (auto p : particles)
			p->Render();
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}