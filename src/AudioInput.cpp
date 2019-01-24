#include "AudioInput.h"
#include "cinder/Log.h"
#include "cinder/audio/dsp/Dsp.h"

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
	return binIndex * (float)mCtx->getSampleRate() / (float)mMonitorSpectralNode->getFftSize(); //
}

float AudioInput::getBinMagnitude(const int binIndex)
{
	return mMagSpectrum[binIndex];
}



void AudioInput::draw()
{

}