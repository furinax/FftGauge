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
	//| debug | AudioInput::setup[29] Microphone (2 - Plantronics GameCom 818)
	//	| debug | AudioInput::setup[29] Microphone (Realtek High Definition Audio)
	//	| debug | AudioInput::setup[29] ASUS VN248 - 4 (NVIDIA High Definition Audio)
	//	| debug | AudioInput::setup[29] ASUS VN248 - 0 (NVIDIA High Definition Audio)
	//	| debug | AudioInput::setup[29] Realtek Digital Output(Optical) (Realtek High Definition Audio)
	//	| debug | AudioInput::setup[29] Speakers(Realtek High Definition Audio)
	//	| debug | AudioInput::setup[29] Realtek Digital Output(Realtek High Definition Audio)
	//	| debug | AudioInput::setup[29] Speakers(2 - Plantronics GameCom 818)
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

	mCentroidFreq = mMonitorSpectralNode->getSpectralCentroid();
	
}

float AudioInput::getVolume()
{
	return mMonitorSpectralNode->getVolume();
}

float AudioInput::getBinFrequency(const int binIndex)
{
	return mMonitorSpectralNode->getFreqForBin(binIndex);
}

float AudioInput::getBinMagnitude(const int binIndex)
{
	return mMagSpectrum[binIndex];
}

void AudioInput::draw()
{
	if (!mVisible)
		return;

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
	float nyquist = (float)audio::master()->getSampleRate() / 2.0f;
	float centroidFreqNormalized = mCentroidFreq / nyquist;

	Rectf bounds = ci::app::getWindowBounds();
	float barCenter = bounds.x1 + centroidFreqNormalized * bounds.getWidth();
	Rectf verticalBar = { barCenter - 2, bounds.y1, barCenter + 2, bounds.y2 };
	gl::ScopedColor colorScope(0.85f, 0.45f, 0, 0.4f); // transparent orange
	gl::drawSolidRect(verticalBar);
}

float AudioInput::getCentroidFrequency()
{
	return mCentroidFreq;
}