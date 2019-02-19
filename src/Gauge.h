#include "cinder/app/App.h"
#include <list>
#include "Particle.h"
#include "cinder/gl/gl.h"

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
	ci::Channel32f mChannel;

	int PARTICLES = 100;
};