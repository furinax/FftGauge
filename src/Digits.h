#pragma once

#include "cinder/app/App.h"
#include "cinder/text.h"
#include "cinder/Font.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include <time.h>

class Digits
{
public:
	Digits::Digits();

	void draw();
	void update();
private:
	ci::Font mFont;
	ci::Color mTextColor;
	ci::gl::Texture2dRef mTex;
	std::time_t mTime;
};