#pragma once

#ifndef RANDOM_SEARCH_H
#define RANDOM_SEARCH_H

#include "MscnProblem.h"



class RandomSearch {
public:
	RandomSearch(int seed);
	void setSeed(int seed);
	double* solveProblem(Problem* problem);
private:
	double* iteration(Problem * problem, std::pair<double, double>* constraints);
	Random rand;
};

#endif