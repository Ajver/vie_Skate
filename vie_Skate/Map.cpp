#include "Map.h"

#include "Ground.h"

Map::Map(b2World* world, vie::ObjectsManager* om) {
	Ground* ground = new Ground(world);
	om->appendObject(ground);
}

Map::~Map() {
}

void Map::render(vie::Graphics* g) {

}
