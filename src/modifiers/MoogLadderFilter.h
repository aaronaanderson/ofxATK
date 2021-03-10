#pragma once

/*

A first pass at a digital Moog Ladder Filter. The primary source material for this 
is based on Will Pirkle's book 'Designing Software SYnthesizer Plug-ins in C++.' 
The first implementation will be a bare-bones ladder filter; the second goal is to 
implement Oberheim variations on the filter to include second and fourth order LPF, 
BPF, and HPFs
*/

/*
The most basic model is 4 lowpass filters in series. The output of the final LPF 
is flipped around 0 (multiplied by -1), multiplied by K, and summed with the next input value
*/

#include "Filters.hpp"

//TODO Make parent class for filters
class LadderFilter  {

public:
	LadderFilter() {
		resonance = 4.0f;
		mostRecentOutput = 0.0f;
		flippedOutput = -0.0f;
		cutOffFrequency = 1000.0f;

		//for (int i = 0; i < 4; i++)
			//lowPassFilters[i] = new LowPass(cutOffFrequency);

	}

	float process(float input);
	void setFrequency(float frequency) {
		for (int i = 0; i < 4; i++)
			lowPassFilters[i].setFreq(frequency);
	}
	void setResonance(float resonance) {this->resonance = resonance;}
	void reset();//TODO add this to all filters. 

private:
	
	LowPass lowPassFilters[4];
	float mostRecentOutput;
	float flippedOutput;//previous output * -1
	float cutOffFrequency;
	float resonance;//this is how much resonance (not mathematically the same as Q, but controlls the same thing) pg333
};