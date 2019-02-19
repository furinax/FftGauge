#include "Gauge.h"
#include "cinder/Path2d.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderGlm.h"
#include "cinder/Rand.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"

Gauge::Gauge()
{
	auto image = ci::loadImage("../assets/nsx2.jpg");
	mChannel = ci::Channel32f(image);

	for (int x = 0; x < mChannel.getWidth(); x += 10)
	{
		for (int y = 0; y < mChannel.getHeight(); y += 10)
		{
			auto pos = ci::vec2(x, y);
			if (mChannel.getValue(pos) > 0.01f)
				mParticles.push_back(Particle(8*mChannel.getValue(pos),pos));
		}
	}
}

void Gauge::draw()
{
	if (!mVisible)
		return;
	ci::gl::pushMatrices();
	ci::gl::translate(ci::vec2(0, 200));
	std::for_each(mParticles.begin(), mParticles.end(), [](Particle &p){p.draw(); });
	ci::gl::popMatrices();
}

void Gauge::update(float const level)
{
	mLevel = level;

	std::for_each(mParticles.begin(), mParticles.end(), [=](Particle &p){p.update(mLevel); });
}