#include "Particle.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderGlm.h"
#include "cinder/Shape2d.h"
#include "cinder/Rand.h"
#include "Colors.hpp"

Particle::Particle(const int radius, const ci::vec2 pos) :
mRadius(radius),
mPos(pos),
mLevel(0),
mPos0(mPos)
{
	mColor = Colors::getRandColor();
}

void Particle::draw()
{
	auto radius = mRadius;
	ci::gl::color(ci::ColorA(mColor, mLevel));
	ci::gl::drawSolidCircle(mPos, radius);

}

void Particle::update(float level)
{
	mLevel = level;
	
}