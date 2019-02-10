#include "Gauge.h"
#include "cinder/Path2d.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderGlm.h"

Gauge::Gauge()
{
	mColor = ci::Color(1.f, 1.f, 1.f);
}

void Gauge::draw()
{
	ci::gl::lineWidth(mLineWidth * mLevel);
	ci::gl::color(mColor);

	for (float i = 0; i < 2 * M_PI * mLevel ; i += 2 * M_PI / SPOKES)
	{
		ci::Path2d path;
		path.arc(ci::app::getWindowCenter(), RADIUS, i - M_PI/2.f, i + (2*M_PI/SPOKES) - mGap - M_PI/2.f, true);
		ci::gl::draw(path);
	}
}

void Gauge::update(float const level)
{
	mLevel = level;
	mColor = level > THRESHOLD ? getThresholdColor() : ci::Color(1.f, 1.f, 1.f);
}

ci::Color Gauge::getThresholdColor()
{
	return ci::app::getElapsedFrames()/5 % 2 == 0 ? ci::Color::black() : ci::Color(1.f, 0, 0);
}