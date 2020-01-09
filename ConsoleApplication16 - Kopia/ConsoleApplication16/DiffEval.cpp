
#include "pch.h"
#include "DiffEval.h"
#include "MySmartPointer.h"
#include <iostream>

void DiffEval::generatePopulation() {
	this->constraints = problem->getConstraints();
	Individual** population = new Individual*[POPULATION_SIZE];
	for (size_t i = 0; i < POPULATION_SIZE; i++)
	{
		//		solution[i] = rand.getDoubleInRange(constraints[i].first, constraints[i].second);
		population[i] = generateIndividual();
	}
	this->population = population;
}

Individual* DiffEval::generateIndividual() {
	int size = problem->getProblemSize();
	double* genotype = new double[size];
	do {
		for (size_t i = 0; i < size; i++)
		{
			//		solution[i] = rand.getDoubleInRange(constraints[i].first, constraints[i].second);
			genotype[i] = rand.getDoubleInRange(0, 3);
		}
	} while (!problem->constaintSatisfied(genotype, size, NULL));
	return new Individual(genotype, size);
}

Individual* DiffEval::solve(Problem* problem,int seed) {
	rand.setSeed(seed);
	fitnessCount = 0;
	this->problem = problem;
	generatePopulation();
	while (!isStopConditionMet()) {
		for (size_t i = 0; i < POPULATION_SIZE; i++)
		{
			MySmartPointer<Individual> baseInd(generateIndividual());
			MySmartPointer<Individual> addInd1(generateIndividual());
			MySmartPointer<Individual> addInd2(generateIndividual());
			if (areDifferent(population[i], baseInd.getPointer(), addInd1.getPointer(), addInd2.getPointer())) {
				Individual* newInd = cross(population[i], baseInd.getPointer(), addInd1.getPointer(), addInd2.getPointer());
				placeBetter(i, newInd);
			}
			fitnessCount++;
		}
	}
	return chooseBest();
}

void DiffEval::placeBetter(int index, Individual* newInd) {
	if (isBetter(population[index], newInd)) {
		delete population[index];
		population[index] = newInd;
	}
	else delete newInd;
}


bool DiffEval::areDifferent(Individual* ind, Individual* base, Individual* indAdd1, Individual* indAdd2) {
	return ind->isDifferent(base) && ind->isDifferent(indAdd1) && ind->isDifferent(indAdd2);
}

bool DiffEval::isStopConditionMet() {
	return fitnessCount >= FITNESS_COUNT_TO_STOP;
}

bool Individual::isDifferent(Individual* other) {
	if (this->size != other->size) return true;
	for (size_t i = 0; i < size; i++)
	{
		if(this->genes[i] != other->genes[i]) return true;
	}
	return false;
}

double Individual::getFitness(Problem* problem) {
	if (result != 0) return result;
	if (problem->getProblemSize() != size) return 0;
	result = problem->getQuality(genes, size, NULL);
	return result;
}

void Individual::printSolution()
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << genes[i] << " ";
	}
    std:cout << result;
}


Individual* DiffEval::cross(Individual* ind, Individual* base, Individual* indAdd1, Individual* indAdd2) {
	double* newGenotype = new double[ind->getSize()];
	for (size_t i = 0; i < ind->getSize(); i++)
	{
		if (rand.getDoubleInRange(0, 1) < CROSS_PROBABILITY) {
			newGenotype[i] = base->getAt(i) + WEIGHT_DIFF * (indAdd1->getAt(i) - indAdd2->getAt(i));
		}
		else newGenotype[i] = ind->getAt(i);
	}
	return new Individual(newGenotype,ind->getSize());
}

bool DiffEval::isBetter(Individual* old, Individual* newInd) {
	double fitness = newInd->getFitness(problem);
	return fitness >= old->getFitness(problem);
}

Individual* DiffEval::chooseBest() {
	double best = population[0]->getResult();
	int index = 0;
	for (size_t i = 0; i < POPULATION_SIZE; i++)
	{
		if (population[i]->getResult() >= best) {
			index = i;
			best = population[i]->getResult();
		}
	}
	return population[index];
}