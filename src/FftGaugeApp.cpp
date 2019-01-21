#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class FftGaugeApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void FftGaugeApp::setup()
{
}

void FftGaugeApp::mouseDown( MouseEvent event )
{
}

void FftGaugeApp::update()
{
}

void FftGaugeApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( FftGaugeApp, RendererGl )
