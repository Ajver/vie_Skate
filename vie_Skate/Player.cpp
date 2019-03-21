#include "Player.h"

#include <vie/Input.h>
#include <vie/Logger.h>
#include <iostream>

class RayCastCallback : public b2RayCastCallback {
public:
	RayCastCallback() :
		was(false)
	{}
	
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
		const b2Vec2& normal, float32 fraction) {
		was = true;
		return 0;
	}

	bool wasReport() const {
		return was;
	}

private:
	bool was;

};

Player::Player(b2World* world) :
	moveTimer(1000)
{
	position = { 0, 0 };
	size = { 1, 2 };

	size *= 0.5f;
	position += size;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = { position.x, position.y };

	b2PolygonShape shape;
	shape.SetAsBox(size.x, size.y);

	size *= 2.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.002f;

	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
}

Player::~Player() {}

void Player::update(float et) {
}

void Player::render(vie::Graphics* g) {
	g->setColor(vie::Color(0, 0, 255));

	position = { body->GetPosition().x, body->GetPosition().y };

	g->rotate(body->GetAngle());
	g->translate(position - size * 0.5f);
	g->fillRect({0,0}, size);
	g->translate(size * 0.5f - position);
	g->rotate(-body->GetAngle());
}

void Player::onKeyPress() {

	b2Vec2 moveVec = { 300.0f, 0 };
	b2Vec2 breakVec = { 10.0f, 0 };

	bool wantMove = false;

	switch (vie::Input::getLastKey()) {
	case SDLK_LEFT:
		if (!isOnTheGround()) {
			return;
		}
		if (body->GetLinearVelocity().x > 0.5f) {
			body->ApplyForceToCenter(-breakVec, true);
			moveTimer.restart();
		}
		else {
			wantMove = moveTimer.tick();
		}
		break;
	case SDLK_RIGHT:
		if (!isOnTheGround()) {
			return;
		}
		if (body->GetLinearVelocity().x < -0.5f) {
			body->ApplyForceToCenter(breakVec, true);
			moveTimer.restart();
		}
		else {
			wantMove = moveTimer.tick();
			moveVec.x *= -1;
		}
		break;
	case SDLK_SPACE:
		if (!spacePressTimer.getIsRunning()) {
			spacePressTimer.start();
		}
		break;
	}

	if (wantMove) {
		moveTimer.restart();
		body->ApplyForceToCenter(-moveVec, true);
	}
}

void Player::onKeyRelease() {
	switch (vie::Input::getLastKey())
	{
	case SDLK_SPACE:		
		if (isOnTheGround()) {
			unsigned long et = spacePressTimer.getElapsedTime();
			spacePressTimer.stop();

			float addForce = et / 500.0f;
			if (addForce > 1.0f)
				addForce = 1.0f;
			addForce *= 200.0f;

			float speedForce = abs(body->GetLinearVelocity().x) / 10.0f;
			if (speedForce > 1.0f)
				speedForce = 1.0f;
			speedForce *= 200.0f;

			float force = 300 + addForce + speedForce;

			body->ApplyForceToCenter(b2Vec2(0, -force), true);
		}
		break;
	}
}

bool Player::isOnTheGround() const {
	RayCastCallback callback;
	body->GetWorld()->RayCast(&callback, body->GetPosition(), body->GetPosition() + b2Vec2(0, size.y*0.5f + 0.1f));
	return callback.wasReport();
}