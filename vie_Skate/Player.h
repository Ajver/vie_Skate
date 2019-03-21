#pragma once

#include <vie/Object.h>
#include <vie/Timer.h>
#include <Box2D/Box2D.h>

class Player : public vie::Object
{
public:
	Player(b2World* world);
	~Player();

	void update(float et);
	void render(vie::Graphics* g);

	void onKeyPress();
	void onKeyRelease();

private:
	b2Body* body;

	vie::Timer moveTimer;
	vie::Timer spacePressTimer;

	bool isOnTheGround() const;
};

