#pragma once

#include <Box2D/Box2D.h>
#include <vie/Graphics.h>
#include <vie/ObjectsManager.h>


class Map
{
public:
	Map(b2World* world, vie::ObjectsManager* om);
	~Map();

	void render(vie::Graphics* g);

private:

};

