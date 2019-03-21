#pragma once

#include <vie/Object.h>
#include <Box2D/Box2D.h>

class Ground : public vie::Object
{
public:
	Ground(b2World* world);
	~Ground();

	void update(float et);
	void render(vie::Graphics* g);

private:
	b2Body* body;

};

