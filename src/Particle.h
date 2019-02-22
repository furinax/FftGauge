#pragma once
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Vbo.h"

class Particle
{
public:
	Particle(const float level, const ci::vec2 pos);
	void draw();
	void update(float level);

	float mRadius;
	ci::ColorA mColor;
	ci::vec2 mPos;
	ci::vec2 mVel;
	ci::vec2 mPos0;
	float mLevel;
	ci::gl::VboMeshRef mCircle;

	int MAX_DISTANCE = 400;
};