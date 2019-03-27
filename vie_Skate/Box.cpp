#include "Box.h"

#include <vie/Random.h>

# define M_PI 3.141592653589793238462643383279502884L 

Box::Box(b2World* world, glm::vec2 pos) :
	texture("res/Graphics/Box.png")
{
	size = { 0.6f, 0.6f };
	position = pos;

	size *= 0.5f;

	float angle = vie::Random::nextInt(4) * M_PI;

	b2BodyDef bodyDef;
	bodyDef.angle = angle;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = { position.x, position.y };

	b2PolygonShape shape;
	shape.SetAsBox(size.x, size.y);

	size *= 2.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 3.0f;
	fixtureDef.friction = 0.3f;
	
	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
}	

Box::~Box() {}

void Box::update(float et) {

}

void Box::render(vie::Graphics* g) {
	position = { body->GetPosition().x, body->GetPosition().y };

	g->rotate(body->GetAngle());
	g->translate(position);
	g->drawTexture(texture, -size*0.5f, size);
	g->translate(-position);
	g->rotate(-body->GetAngle());
}

