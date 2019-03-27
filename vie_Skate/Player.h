#pragma once

#include <vie/Timer.h>
#include <vie/Object.h>
#include <vie/ObjectsManager.h>
#include <Box2D/Box2D.h>

class Board;
class Player : public vie::Object
{
public:
	Player(vie::ObjectsManager* om, b2World* world);
	~Player();

	void update(float et);
	void render(vie::Graphics* g);

	void onKeyPress();
	void onKeyRelease();

	bool isOnTheGround() const;

private:
	b2Body* body;
	b2Joint* joint;
	Board* board;

	vie::Timer moveTimer;
	vie::Timer spacePressTimer;

	vie::Texture texture;

};

