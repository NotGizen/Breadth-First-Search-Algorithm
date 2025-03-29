#include "precomp.h"
#include "Ball.h"

Ball::Ball()
{
	sprite = new Surface("assets/ball.png");
}

Ball::~Ball()
{
	delete sprite;
}
