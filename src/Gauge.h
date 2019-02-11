#include "cinder/app/App.h"
#include <list>
#include "Particle.h"

class Gauge
{
public:
	Gauge();
	void draw();
	void update(float const level);

	float mLevel = 0.f;
	bool mVisible = true;
	ci::ivec2 mCenter;
	std::list<Particle> mParticles;

	int PARTICLES = 10;
};