#pragma once
class Animation
{
public:
	int row, frames, speed;
	Animation();
	Animation(int row, int frames, int speed);
	void setSpeed(int speed);
};

