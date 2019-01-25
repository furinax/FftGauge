#include "cinder/app/App.h"

class Gauge
{
public:
	void draw();
	void update(float const level);

	float mLevel = 0.f;
	ci::ivec2 mCenter;
};