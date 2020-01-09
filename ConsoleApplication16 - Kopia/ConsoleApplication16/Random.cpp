#include "pch.h"
#include "Random.h"

void Random::setSeed(int seed) {
	this->gen = new std::mt19937(seed);
}

double Random::getDoubleInRange(double min, double max) {
	std::uniform_real_distribution<> dis(min,max);
	return dis(*gen);
}

int Random::getIntegerInRange(int min,int max) {
	std::uniform_int_distribution<> dis(min, max);
	return dis(*gen);
}