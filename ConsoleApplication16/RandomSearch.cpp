#include "pch.h"
#include "RandomSearch.h"
#include "Problem.h"
#include "Random.h"

RandomSearch::RandomSearch(int seed) {
	rand.setSeed(seed);
}

void RandomSearch::setSeed(int seed) {
	rand.setSeed(seed);
}

double* RandomSearch::solveProblem(Problem* problem) {
	double* result = NULL;
	std::pair<double, double>* constraints = problem->getConstraints();
	do{
		if(result != NULL) delete[] result;
		result = iteration(problem,constraints);
	} while (!problem->checkConstraints());
    return result;
}

double* RandomSearch::iteration(Problem* problem, std::pair<double, double>* constraints) {
	int size = problem->getProblemSize();
	double* solution = new double[size];
	for (size_t i = 0; i < size; i++)
	{
		   solution[i] = rand.getDoubleInRange(constraints[i].first, constraints[i].second);
		// solution[i] = rand.getDoubleInRange(0, 3);
	}
	double result = problem->getQuality(solution, size, NULL);
	return solution;
}