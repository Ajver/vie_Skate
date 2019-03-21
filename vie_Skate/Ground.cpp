#include "Ground.h"


Ground::Ground(b2World* world) {
	size = { 30, 2 };
	position = { -size.x*0.5f, 3 };

	size *= 0.5f;
	position += size;

	b2BodyDef bodyDef;
	bodyDef.position = { position.x, position.y };

	b2PolygonShape shape;
	shape.SetAsBox(size.x, size.y);

	size *= 2.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
}

Ground::~Ground() {}

void Ground::update(float et) {

}

void Ground::render(vie::Graphics* g) {
	g->setColor(vie::Color(128, 128, 255));

	position = { body->GetPosition().x, body->GetPosition().y };

	g->rotate(body->GetAngle());
	g->translate(position - size * 0.5f);
	g->fillRect({ 0,0 }, size);
	g->translate(size * 0.5f - position);
	g->rotate(-body->GetAngle());
}

