#include "cinder/app/App.h"
#include "cinder/text.h"
#include "cinder/Font.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

class Digits
{
public:
	Digits::Digits();

	void draw();
	void update(const int input);
private:
	ci::Font mFont;
	ci::Color mTextColor;
	ci::gl::Texture2dRef mTex;

	int mValue;
};