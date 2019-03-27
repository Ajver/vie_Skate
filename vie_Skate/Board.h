#pragma once

#include <vie/Object.h>
#include <Box2D/Box2D.h>

class Board : public vie::Object
{
public:
	Board(b2World* world);
	~Board();

	void init(b2Body* nbody);

	void update(float et);
	void render(vie::Graphics* g);

	bool isOnTheGround() const;

	b2Body* getBody() const;

private:
	b2Body* body;
	vie::Texture texture;

};

