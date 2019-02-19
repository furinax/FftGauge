#pragma once
#include "cinder/app/App.h"

class Particle
{
public:
	Particle(const int radius, const ci::vec2 pos);
	void draw();
	void update(float level);

	int mRadius;
	ci::Color mColor;
	ci::vec2 mPos;
	ci::vec2 mVel;
	ci::vec2 mPos0;
	float mLevel;

	int MAX_DISTANCE = 400;
};