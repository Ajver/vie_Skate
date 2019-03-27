#pragma once

#include <vie/Object.h>
#include <Box2D/Box2D.h>

class Box : public vie::Object
{
public:
	Box(b2World* world, glm::vec2 pos);
	~Box();

	void update(float et);
	void render(vie::Graphics* g);

private:
	b2Body* body;

	vie::Texture texture;

};

