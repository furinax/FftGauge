#include "Gauge.h"
#include "cinder/Path2d.h"
#include "cinder/gl/gl.h"


void Gauge::draw()
{
	ci::Path2d path;
	path.arc(ci::app::getWindowCenter(), 200.f, 2.f * M_PI * mLevel - M_PI / 2.f, M_PI / -2.f, false);
	ci::gl::lineWidth(5.f);
	ci::gl::draw(path);
}

void Gauge::update(float const level)
{
	mLevel = level;
}