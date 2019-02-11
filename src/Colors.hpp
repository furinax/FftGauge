#pragma once
#include "cinder/app/App.h"
#include "cinder/Rand.h"

class Colors
{
public:
	static ci::Color getRandColor() { 
		static std::vector<ci::Color> m = std::vector < ci::Color > {
			ci::Color(1, 0, 0), ci::Color(1, 1, 0), ci::Color(0, 1, 0), ci::Color(0, 1, 1), ci::Color(0, 0, 1),
		};
		return m[(int)(ci::randFloat() * m.size())]; };

private:
	Colors();
};


