#include "Data.h"

#include <algorithm>

Data::Data()
{

}

float Data::maxFreq()
{
	return mMaxFreq;
}

float Data::minFreq()
{
	return mMinFreq;
}

float Data::idle()
{
	return mIdleAmplitude;
}

void Data::update(const float freq, const float amplitude)
{

	if (mIdleAmplitude == 0 && mAmplitudes.size() >= MAX_VALUES)
	{
		mIdleAmplitude = *std::max_element(mAmplitudes.begin(), mAmplitudes.end());
	}
	else if (mAmplitudes.size() < MAX_VALUES)
		mAmplitudes.push_front(amplitude);

	if (amplitude > mIdleAmplitude * IDLE_THRESHOLD)
	{
		mFrequencies.push_front(freq);
		if (mFrequencies.size() > MAX_VALUES)
			mFrequencies.pop_back();

		mMaxFreq = std::max(mMaxFreq, *std::max_element(mFrequencies.begin(), mFrequencies.end()));
		mMinFreq = std::min(mMinFreq, *std::min_element(mFrequencies.begin(), mFrequencies.end()));
	}

}