#include "Particle.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderGlm.h"
#include "cinder/Shape2d.h"
#include "cinder/Rand.h"
#include "Colors.hpp"

Particle::Particle(const float level, const ci::vec2 pos) :
mRadius(5),
mPos(pos),
mLevel(level),
mPos0(mPos)
{
	mColor = ci::ColorA(1.f, 1.f, 1.f, level);
	auto circle = ci::geom::Circle();
	circle.center(mPos).radius(mRadius);
	
	mCircle = ci::gl::VboMesh::create(circle);
}

void Particle::draw()
{
	auto radius = mRadius;
	ci::gl::color(mColor);
	ci::gl::draw(mCircle);
	
	//ci::gl::drawSolidCircle(mPos, radius);

}

void Particle::update(float level)
{
	mLevel = level;
	mRadius = 5.f * mLevel + 1.f;
}