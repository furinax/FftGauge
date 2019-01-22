#include "cinder/app/App.h"

class Gauge
{
public:
	void draw();
	void update(float const level);

	float mLevel;
	ci::ivec2 mCenter;
};