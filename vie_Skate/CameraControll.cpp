#include "CameraControll.h"



CameraControll::CameraControll(Player* np, vie::Camera2D* ncam) :
	player(np),
	camera(ncam)
{
}

CameraControll::~CameraControll()
{
}

void CameraControll::update(float et) {
	glm::vec2 targetPosition = player->getPosition() + player->getSize() * 0.5f;
	glm::vec2 cameraPosition = camera->getPosition();
	glm::vec2 diff = cameraPosition - targetPosition;

	float mod = 3.0f * et;
	if (mod > 1.0f) mod = 1.0f;

	glm::vec2 newCamPos = cameraPosition - diff * mod;
	
	camera->setPosition(newCamPos);
}