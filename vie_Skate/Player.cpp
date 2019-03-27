#include "Player.h"
#include "Board.h"

#include <vie/Input.h>
#include <vie/Logger.h>
#include <iostream>

Player::Player(vie::ObjectsManager* om, b2World* world) :
	moveTimer(1000),
	board(new Board(world)),
	texture("res/Graphics/Human.png")
{
	position = { 0, 0 };
	size = { 0.50f, 1.55f };

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = { position.x, position.y };

	b2PolygonShape shape;
	shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 3.0f;
	fixtureDef.friction = 2.0f;

	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);

	board->init(body);
	om->appendObject(board);

	b2DistanceJointDef jointDef;
	b2Vec2 footPosition = body->GetPosition();
	footPosition.y + size.y * 0.4f;
	jointDef.Initialize(body, board->getBody(), footPosition, board->getBody()->GetPosition());
	jointDef.collideConnected = true;
	jointDef.frequencyHz = 4.0f;
	jointDef.dampingRatio = 1.0f;
	joint = world->CreateJoint(&jointDef);
}

Player::~Player() {}

void Player::update(float et) {
	b2Vec2 moveVec = { 250.0f, 0 };
	b2Vec2 breakVec = { 10.0f, 0 };
	b2Vec2 footPosition = body->GetPosition();

	bool wantMove = false;

	if (vie::Input::isKeyPressed(SDLK_LEFT)) {
		if (!isOnTheGround()) {
			return;
		}
		if (body->GetLinearVelocity().x > 0.5f) {
			body->ApplyForce(-breakVec, footPosition, true);
			moveTimer.restart();
		}
		else {
			wantMove = moveTimer.tick();
		}
	}
	if (vie::Input::isKeyPressed(SDLK_RIGHT)) {
		if (!isOnTheGround()) {
			return;
		}
		if (body->GetLinearVelocity().x < -0.5f) {
			body->ApplyForce(breakVec, footPosition, true);
			moveTimer.restart();
		}
		else {
			wantMove = moveTimer.tick();
			moveVec.x *= -1;
		}
	}
	if (vie::Input::isKeyPressed(SDLK_SPACE)) {
		if (!spacePressTimer.getIsRunning()) {
			spacePressTimer.start();
		}
	}

	if (vie::Input::isKeyPressed(SDLK_TAB)) {
		
	}

	if (wantMove) {
		moveTimer.restart();
		body->ApplyForceToCenter(-moveVec, true);
	}
}

void Player::render(vie::Graphics* g) {
	position = { body->GetPosition().x, body->GetPosition().y };

	g->rotate(body->GetAngle());
	g->translate(position);
	g->drawTexture(texture, { -size.y * 0.5f, -size.y * 0.5f }, { size.y, size.y });
	g->translate(-position);
	g->rotate(-body->GetAngle());
}

void Player::onKeyPress() {
	
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
			addForce *= 570.0f;
			
			float force = 150 + addForce;

			body->ApplyForceToCenter(b2Vec2(0, -force), true);
		}
		break;
	}
}

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

bool Player::isOnTheGround() const {
	RayCastCallback callback;
	body->GetWorld()->RayCast(&callback, body->GetPosition(), body->GetPosition() + b2Vec2(0, size.y*0.5f + 0.1f));
	return callback.wasReport();
}