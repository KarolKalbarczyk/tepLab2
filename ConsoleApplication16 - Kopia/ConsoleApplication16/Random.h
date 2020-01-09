#pragma once

#ifndef RANDOM_H
#define RANDOM_H


#include <random>


class Random {
public:
	void setSeed(int seed);
	double getDoubleInRange(double min, double max);
	int getIntegerInRange(int min, int max);
private:
	int seed;
	std::mt19937* gen;

};

#endif