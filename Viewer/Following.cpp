#include "stdafx.h"
#include "Following.h"

Following::Following(IFollowing * focus):
	focus(focus)
{
}

Following::~Following()
{
}

void Following::Change(IFollowing * focus)
{
	this->focus = focus;
}

void Following::Update()
{
	if (focus == NULL)
		return;

	D3DXVECTOR2 location, size;
	focus->Focus(&location, &size);

	//TODO: Alter and Clamp the camera so that it follow the character like mario camera
	//Maybe create another class?

	//?? How to check where is the center of the screen
	//Lets gather the factors....

	//position is the position of the camera, in world vector
	//No, position is the left down point of the view...
	//is Width is the size of the camera?
	//it is Width/WindowScale.x
	//then center of screen is width/windowscale.x/2
	//zero is position.x

	if (location.x + size.x / 2 > position.x + Width / WindowScale.x / 2) {
		//if mario's right side is > than the center of screen, then screen shift
		position.x = location.x + size.x / 2 - Width / WindowScale.x / 2;
		for (auto iter = plan.begin(); iter != plan.end();) {
			//if plan's left is less than full of the screen, then plan is instantiated
			if ((*iter)->Position().x + (*iter)->Size().x / 2 > position.x) {
				(*iter)->isAlive = true;
				alive.push_back((*iter));
				iter = plan.erase(iter);
			}
			else {
				iter++;
			}
		}
	}
	else if (location.x - size.x / 2 < position.x) {
		// if mario's left side is < than the 0 of screen, then mario is clamped
		location.x = position.x + size.x/2;
		focus->Position(location);
	}

	for (auto iter = alive.begin(); iter != alive.end();) {
		//if object's right is less than 0 of the screen, then object is removed
		if ((*iter)->Position().x + (*iter)->Size().x / 2 < position.x) {
			(*iter)->isAlive = false;
			iter = alive.erase(iter);
		}
		else {
			iter++;
		}
	}

	//position = temp;

	__super::Update();
}

void Following::Initialize()
{
	for (auto iter = plan.begin(); iter != plan.end();) {
		//if plan's left is less than full of the screen, then plan is instantiated
		if ((*iter)->Position().x + (*iter)->Size().x / 2 > position.x) {
			(*iter)->isAlive = true;
			alive.push_back((*iter));
			iter = plan.erase(iter);
		}
		else {
			iter++;
		}
	}
}
