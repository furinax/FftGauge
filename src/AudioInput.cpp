#include "AudioInput.h"
#include "cinder/Log.h"
#include "cinder/audio/dsp/Dsp.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace std;

AudioInput::AudioInput()
{

}

AudioInput::~AudioInput()
{

}

void AudioInput::setup()
{
	//Microphone (Realtek High Definition Audio)
	//Realtek Digital Output(Realtek High Definition Audio)
	//Realtek Digital Output(Optical) (Realtek High Definition Audio)
	//ASUS VN248 - 4 (NVIDIA High Definition Audio)
	//ASUS VN248 - 0 (NVIDIA High Definition Audio)
	auto inputs = audio::Device::getDevices();
	for (auto i : inputs)
	{
		 CI_LOG_D(i->getName() );
	}

	auto dev = audio::Device::findDeviceByName("Microphone (Realtek High Definition Audio)");
	mCtx = audio::Context::master();
	mInputDeviceNode = mCtx->createInputDeviceNode(dev);
	auto format = audio::MonitorSpectralNode::Format().fftSize(2048).windowSize(4096);
	mMonitorSpectralNode = mCtx->makeNode(new audio::MonitorSpectralNode(format));
	mMonitor = mCtx->makeNode(new audio::MonitorNode(format));
	mGain = mCtx->makeNode(new audio::GainNode);
	mGain->setValue(10.f);
	mInputDeviceNode >> mGain >> mMonitorSpectralNode >> mMonitor;
	mInputDeviceNode->enable();
	mCtx->enable();

}

void AudioInput::update()
{
	mMagSpectrum = mMonitorSpectralNode->getMagSpectrum();
	ci::audio::dsp::normalize(&mMagSpectrum[0], mMagSpectrum.size(), 1.f);
}

float AudioInput::getVolume()
{
	return mMonitorSpectralNode->getVolume();
}

float AudioInput::getBinFrequency(const int binIndex)
{
	return mMonitorSpectralNode->getFreqForBin(binIndex);//binIndex * (float)mCtx->getSampleRate() / (float)mMonitorSpectralNode->getFftSize();
}

float AudioInput::getBinMagnitude(const int binIndex)
{
	return mMagSpectrum[binIndex];
}

float AudioInput::getCenter()
{
	return mMonitorSpectralNode->getSpectralCentroid();
}

void AudioInput::draw()
{
	ci::Path2d path;
	path.moveTo(ci::ivec2(0, ci::app::getWindowHeight()));
	for (int i = 0; i < mMagSpectrum.size(); i++)
	{
		path.lineTo(ci::ivec2(i, ci::app::getWindowHeight()));
		path.lineTo(ci::ivec2(i, ci::app::getWindowHeight() * (1.f - getBinMagnitude(i))));
	}

	ci::gl::lineWidth(5.f);
	ci::gl::color(ci::Color::white());
	ci::gl::draw(path);
	drawSpectralCentroid();


}

void AudioInput::drawSpectralCentroid()

{

	float spectralCentroid = mMonitorSpectralNode->getSpectralCentroid();
	float nyquist = (float)audio::master()->getSampleRate() / 2.0f;

	Rectf bounds = ci::app::getWindowBounds();
	float freqNormalized = spectralCentroid / nyquist;

	float barCenter = bounds.x1 + freqNormalized * bounds.getWidth();
	Rectf verticalBar = { barCenter - 2, bounds.y1, barCenter + 2, bounds.y2 };
	gl::ScopedColor colorScope(0.85f, 0.45f, 0, 0.4f); // transparent orange
	gl::drawSolidRect(verticalBar);
}