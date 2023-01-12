#include "Animation.h"

Animation::Animation()
{
	row = 0;
	frames = 0;
	speed = 100;
}

Animation::Animation(int row, int frames, int speed)
{
	this->row = row;
	this->frames = frames;
	this->speed = speed;
}
void Animation::setSpeed(int speed)
{
	this->speed = speed;
}
