#include "Gauge.h"
#include "cinder/Path2d.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderGlm.h"
#include "cinder/Rand.h"

Gauge::Gauge()
{
	for (int i = 0; i < PARTICLES; i++)
	{
		mParticles.push_back(Particle(ci::randInt(32, 128), ci::randVec2()));
	}
}

void Gauge::draw()
{
	if (!mVisible)
		return;
	std::for_each(mParticles.begin(), mParticles.end(), [](Particle &p){p.draw(); });
}

void Gauge::update(float const level)
{
	mLevel = level;
	std::for_each(mParticles.begin(), mParticles.end(), [=](Particle &p){p.update(mLevel); });
}