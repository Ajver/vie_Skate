#include "Board.h"

#include <vie/Input.h>

Board::Board(b2World* world) :
	texture("res/Graphics/Board.png")
{
}

Board::~Board() {}

void Board::init(b2Body* nbody) {
	size = { 1.2f, 0.290f };
	position = { 0, 0.85 + size.y*0.5f };

	b2BodyDef bodyDef;
	bodyDef.bullet = true;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = { position.x, position.y };

	body = nbody->GetWorld()->CreateBody(&bodyDef);

	b2CircleShape leftWheelShape;
	b2CircleShape rightWheelShape;
	float wheelRadius = size.x * 0.045f;
	leftWheelShape.m_p.Set(-size.x * 0.25f, size.y * 0.39);
	rightWheelShape.m_p.Set(+size.x * 0.25f, size.y * 0.39);

	leftWheelShape.m_radius =
		rightWheelShape.m_radius = wheelRadius;

	b2FixtureDef leftWheelsFixture;
	b2FixtureDef rightWheelsFixture;

	leftWheelsFixture.shape = &leftWheelShape;
	rightWheelsFixture.shape = &rightWheelShape;

	leftWheelsFixture.density =
		rightWheelsFixture.density = 0.4f;
	leftWheelsFixture.friction =
		rightWheelsFixture.friction = 0.002f;

	b2Vec2 haflSize = { size.x * 0.5f, size.y * 0.5f };
	b2Vec2* pointsTop = new b2Vec2[4];
	b2Vec2* pointsTL = new b2Vec2[4];
	b2Vec2* pointsTR = new b2Vec2[4];

	pointsTop[0] = { -haflSize.x*0.4f, -haflSize.y*0.143f };
	pointsTop[1] = { -pointsTop[0].x, pointsTop[0].y };
	pointsTop[2] = { haflSize.x*0.5333f, 0.0f };
	pointsTop[3] = { -pointsTop[2].x, pointsTop[2].y };

	pointsTL[0] = -haflSize;
	pointsTL[1] = { -haflSize.x*0.9333f, -haflSize.y };
	pointsTL[2] = pointsTop[0];
	pointsTL[3] = { -pointsTop[2].x, pointsTop[2].y };

	pointsTR[0] = { -pointsTL[0].x, pointsTL[0].y };
	pointsTR[1] = { -pointsTL[1].x, pointsTL[1].y };
	pointsTR[2] = { -pointsTL[2].x, pointsTL[2].y };
	pointsTR[3] = { -pointsTL[3].x, pointsTL[3].y };

	b2PolygonShape topShape;
	b2PolygonShape topLeftShape;
	b2PolygonShape topRightShape;

	topShape.Set(pointsTop, 4);
	topLeftShape.Set(pointsTL, 4);
	topRightShape.Set(pointsTR, 4);

	b2FixtureDef topOfBoard;
	b2FixtureDef TLOfBoard;
	b2FixtureDef TROfBoard;
	topOfBoard.shape = &topShape;
	TLOfBoard.shape = &topLeftShape;
	TROfBoard.shape = &topRightShape;
	topOfBoard.density =
		TLOfBoard.density =
		TROfBoard.density = 1.0f;
	topOfBoard.friction =
		TLOfBoard.friction =
		TROfBoard.friction = 20.0f;

	body->CreateFixture(&topOfBoard);
	body->CreateFixture(&TLOfBoard);
	body->CreateFixture(&TROfBoard);
	body->CreateFixture(&leftWheelsFixture);
	body->CreateFixture(&rightWheelsFixture);
}

void Board::update(float et) {
	b2Vec2 pos = body->GetPosition();
	float angle = body->GetAngle();
	
	float speed = 4.0f;
	float angSpeed = 1.0f;

	if (vie::Input::isKeyPressed(SDLK_LCTRL)) {
		if (body->GetGravityScale() == 1.0f) {
			body->SetGravityScale(0.0f);
			body->SetLinearVelocity({ 0, 0 });
			body->SetAngularVelocity(0);
		}
		else {
			body->SetGravityScale(1.0f);
		}
	}

	if (vie::Input::isKeyPressed(SDLK_w)) {
		pos.y -= speed * et;
	}
	if (vie::Input::isKeyPressed(SDLK_s)) {
		pos.y += speed * et;
	}

	if (vie::Input::isKeyPressed(SDLK_a)) {
		pos.x -= speed * et;
	}
	if (vie::Input::isKeyPressed(SDLK_d)) {
		pos.x += speed * et;
	}

	if (vie::Input::isKeyPressed(SDLK_z)) {
		angle -= angSpeed * et;
	}
	if (vie::Input::isKeyPressed(SDLK_x)) {
		angle += angSpeed * et;
	}

	body->SetTransform(pos, angle);
}

void Board::render(vie::Graphics* g) {
	position = { body->GetPosition().x, body->GetPosition().y };

	g->rotate(body->GetAngle());
	g->translate(position);
	g->drawTexture(texture , -size * 0.5f, size);
	g->translate(-position);
	g->rotate(-body->GetAngle());
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

bool Board::isOnTheGround() const {
	RayCastCallback callback;
	body->GetWorld()->RayCast(&callback, body->GetPosition(), body->GetPosition() + b2Vec2(0, size.y*0.5f + 0.1f));
	return callback.wasReport();
}

b2Body* Board::getBody() const {
	return body;
}