#include "Map.h"

#include "Ground.h"
#include "Box.h"

Map::Map(b2World* world, vie::ObjectsManager* om) {
	Ground* ground = new Ground(world);
	om->appendObject(ground);

	Box* box = new Box(world, {3, 0});
	Box* box2 = new Box(world, {-3, 0});

	om->appendObject(box);
	om->appendObject(box2);
}

Map::~Map() {
}

void Map::render(vie::Graphics* g) {

}
