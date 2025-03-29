#pragma once
class Ball
{
public:
	Ball();
	~Ball();
	Surface* sprite = nullptr;
	int2 pos = int2(0, 0);
};

