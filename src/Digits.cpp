#include "Digits.h"


Digits::Digits()
{
	mFont = ci::Font("Calibri", 128);
	mTextColor = ci::Color::white();
}

void Digits::draw()
{
	char buffer[20];
	struct tm * timeinfo = localtime(&mTime);
	time(&mTime);
	strftime(buffer, sizeof(buffer), "%H:%M", timeinfo);

	ci::TextBox textBox;
	textBox = ci::TextBox().font(mFont)
		.size(ci::ivec2(ci::TextBox::GROW, ci::TextBox::GROW))
		.color(mTextColor)
		.alignment(ci::TextBox::CENTER)
		.text(std::string(buffer))
		.premultiplied();
	mTex = ci::gl::Texture2d::create(textBox.render());

	ci::gl::pushMatrices();
	ci::gl::translate(ci::app::getWindowWidth()*.5f-128,ci::app::getWindowHeight()*.5f-64);
	ci::gl::draw(mTex);
	ci::gl::popMatrices();
}

void Digits::update()
{
	mTime = std::time(0);
}