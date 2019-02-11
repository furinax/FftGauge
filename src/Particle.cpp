#include "Particle.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderGlm.h"
#include "cinder/Shape2d.h"
#include "cinder/Rand.h"
#include "Colors.hpp"

Particle::Particle(const int radius, const ci::vec2 pos) :
mRadius(radius),
mPos(100.f*pos),
mLevel(0),
mPos0(mPos)
{
	mColor = Colors::getRandColor();
}

void Particle::draw()
{
	ci::gl::pushMatrices();
	ci::gl::translate(ci::app::getWindowCenter());
	ci::Shape2d shape;
	shape.arc(mPos, mRadius, 0, 2 * M_PI);
	ci::gl::color(mColor);
	ci::gl::draw(shape);
	ci::gl::popMatrices();
}

void Particle::update(float level)
{
	mLevel = level;
	
	auto c = glm::rotate(glm::tvec2<float, glm::precision::highp >(mPos0), (float)ci::app::getElapsedSeconds());
	mVel = c * mLevel - .1f*(mPos);
	mPos += mVel;
}