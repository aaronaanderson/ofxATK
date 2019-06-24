

#include "MoogLadderFilter.h"

void LadderFilter::reset() {

	for (int i = 0; i < 4; i++) {
		lowPassFilters[i].setFreq(cutOffFrequency);
	}
}

float LadderFilter::process(float input) {

	//add the previous output to the input
	float currentSample = input + flippedOutput;

	//process all 4 lowpass filters
	for (int i = 0; i < 4; i++) {
		currentSample = lowPassFilters[i].filter(currentSample);//TODO change filter to process
	}

	flippedOutput = currentSample * resonance * -   1;//scale by k(resonance), the resonance factor; (I think a k of 4 = a Q of 1)

	return currentSample;
}