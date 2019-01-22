#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "Gauge.h"
#include "Digits.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class FftGaugeApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void mouseMove(MouseEvent event) override;
	void update() override;
	void draw() override;

private:
	Gauge mGauge;
	Digits mDigits;

	ci::ivec2 mMousePos;
};

void FftGaugeApp::setup()
{
	setWindowSize(800, 800);
	mMousePos.x = 0;
	mMousePos.y = 0;
}

void FftGaugeApp::mouseMove(MouseEvent event){
	mMousePos = event.getPos();
}

void FftGaugeApp::mouseDown( MouseEvent event )
{
}

void FftGaugeApp::update()
{
	float level = (float)mMousePos.y / (float)getWindowHeight();
	mGauge.update(level);
	mDigits.update(100 * level);
}

void FftGaugeApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
	mGauge.draw();
	mDigits.draw();
}

CINDER_APP( FftGaugeApp, RendererGl )
