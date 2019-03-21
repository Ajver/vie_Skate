#pragma once

#include "Player.h"

class CameraControll
{
public:
	CameraControll(Player* np, vie::Camera2D* ncam);
	~CameraControll();

	void update(float et);

private:
	Player* player;
	vie::Camera2D* camera;
};

