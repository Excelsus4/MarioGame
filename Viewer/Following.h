#pragma once
#include "IFollowing.h"
#include "Camera.h"
#include "Entity/IGravity.h"
#include "Viewer/IViewDrivenLife.h"

class Following : public Camera{
public:
	Following(IFollowing* focus = NULL);
	virtual ~Following();

	void Change(IFollowing* focus);
	virtual void Update() override;

	void Initialize();

	vector<IViewDrivenLife*> plan;
	vector<IViewDrivenLife*> alive;
private:
	IFollowing* focus;
};