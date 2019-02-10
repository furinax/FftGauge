#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "cinder/Log.h"

#include "Gauge.h"
#include "Digits.h"
#include "AudioInput.h"
#include "Data.h"

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
	void enableFileLogging();
	Gauge mGauge;
	Digits mDigits;
	AudioInput mAudioInput;
	bool mDisplayInput = true;
	Data mData;
	ci::params::InterfaceGlRef mParams;
	
	ci::ivec2 mMousePos;
	float mStartupLevel = 0;
};

void FftGaugeApp::setup()
{
	setWindowSize(800, 800);
	mMousePos.x = 0;
	mMousePos.y = 0;
	mAudioInput.setup();

	mParams = ci::params::InterfaceGl::create("My Params", ci::ivec2(100, 100));
	mParams->addParam("Display Input?", &mDisplayInput, false);
}

void FftGaugeApp::mouseMove(MouseEvent event){
	mMousePos = event.getPos();
}

void FftGaugeApp::mouseDown( MouseEvent event )
{
}

void FftGaugeApp::enableFileLogging()

{

	//! This call will append log messages to the file `cinder.log` in the folder `/logs`.
	//! If the folder path `/logs` does not exist, it will be created for you.
	log::makeLogger<log::LoggerFile>("/logs/cinder.log", true);

}

void FftGaugeApp::update()
{
	mAudioInput.update();
	if (mStartupLevel < 1.f)
	{
		mGauge.update(mStartupLevel);
		mDigits.update();
		mStartupLevel += .01f;
	}
	else
	{
		mData.update(mAudioInput.getCentroidFrequency(), mAudioInput.getVolume());
		mGauge.update(mAudioInput.getVolume());
		mDigits.update();
	}

}

void FftGaugeApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
	mGauge.draw();
	mDigits.draw();
	mParams->draw();
	if ( mDisplayInput)
		mAudioInput.draw();
}

CINDER_APP( FftGaugeApp, RendererGl )
