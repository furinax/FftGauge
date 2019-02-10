#include "cinder/app/App.h"

class Gauge
{
public:
	Gauge();
	void draw();
	void update(float const level);
	ci::Color getThresholdColor();

	float mLevel = 0.f;
	ci::ivec2 mCenter;
	ci::Color mColor;
	int mLineWidth = 10;

	float THRESHOLD = .7f; //level where the color changes
	float SPOKES = 16.f;
	int RADIUS = 200;
	float mGap = .05f;
};