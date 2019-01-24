#pragma once

#include "cinder/app/App.h"

#include "cinder/audio/MonitorNode.h"
#include "cinder/audio/Utilities.h"
#include "cinder/audio/GainNode.h"
#include "cinder/Vector.h"

class AudioInput
{
public:
	AudioInput();
	~AudioInput();
	void setup();
	void update();
	void draw();
	float getVolume();
	float getBinFrequency(const int binIndex);
	float getBinMagnitude(const int binIndex);

private:
	ci::audio::Context*					mCtx;
	ci::audio::InputDeviceNodeRef		mInputDeviceNode;
	ci::audio::MonitorSpectralNodeRef	mMonitorSpectralNode;
	ci::audio::MonitorNodeRef			mMonitor;
	ci::audio::GainNodeRef mGain;
	std::vector<float>					mMagSpectrum;
};