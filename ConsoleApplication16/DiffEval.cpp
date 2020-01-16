
#include "pch.h"
#include "DiffEval.h"
#include "MySmartPointer.h"
#include <iostream>

void DiffEval::generatePopulation() {
	this->constraints = problem->getConstraints();
	Individual** population = new Individual*[POPULATION_SIZE];
	for (size_t i = 0; i < POPULATION_SIZE; i++)
	{
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
			genotype[i] = rand.getDoubleInRange(constraints[i].first, constraints[i].second);
		}
	} while (!problem->constaintSatisfied(genotype, size, NULL));
	return new Individual(genotype, size);
}

Individual* DiffEval::solve(Problem* problem,int seed) {
	rand.setSeed(seed);
	this->problem = problem;
	problem->setFitnessCount(0);
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
	return problem->getFitnessCount() >= FITNESS_COUNT_TO_STOP;
}

bool Individual::isDifferent(Individual* other) {
	if (this->size != other->size) return true;
	for (size_t i = 0; i < size; i++)
	{
		if(this->genes[i] != other->genes[i]) return true;
	}
	return false;
}

double Individual::calcFitness(Problem* problem) {
	if (checked) return fitness;
	if (problem->getProblemSize() != size) return 0;
	fitness = problem->getQuality(genes, size, NULL);
	checked = true;
	return fitness;
}

void Individual::printSolution()
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << genes[i] << " ";
	}
    std:cout << fitness;
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
	double fitness = newInd->calcFitness(problem);
	return fitness >= old->calcFitness(problem);
}

Individual* DiffEval::chooseBest() {
	double best = population[0]->getFitness();
	int index = 0;
	for (size_t i = 0; i < POPULATION_SIZE; i++)
	{
		if (population[i]->getFitness() >= best) {
			index = i;
			best = population[i]->getFitness();
		}
	}
	return population[index];
}