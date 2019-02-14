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
	mAngularK = ci::randFloat(1.f, 4.f);
}

void Particle::draw()
{
	auto radius = (mLevel + .5f) * mRadius;
	ci::gl::pushMatrices();
	ci::gl::translate(ci::app::getWindowCenter());
	ci::gl::color(ci::ColorA(mColor, mLevel));
	ci::gl::drawSolidCircle(mPos, radius);
	ci::gl::color(ci::Color::white());
	ci::gl::drawSolidCircle(mPos, radius * .8f);
	ci::gl::popMatrices();
}

void Particle::update(float level)
{
	mLevel = level;
	
	auto c = glm::length(mPos) < MAX_DISTANCE ? glm::rotate(glm::tvec2<float, glm::precision::highp >(mPos0), (float)ci::app::getElapsedSeconds() * mAngularK) : ci::vec2(0,0);
	mVel = c * mLevel - .1f*(mPos);
	mPos += mVel;
}