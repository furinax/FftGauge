#include <deque>

class Data {
public:
	Data();

	void update(const float freq, const float amplitude);
	float maxFreq();
	float minFreq();
	float idle();

private:
	std::deque<float> mFrequencies;
	std::deque<float> mAmplitudes;

	const int MAX_VALUES = 100;
	const float IDLE_THRESHOLD = 1.1f;
	float mMaxFreq = 0, mMinFreq = 1, mIdleAmplitude = 0;
};