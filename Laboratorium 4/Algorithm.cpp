#include "pch.h"
#include "Algorithm.h"
#include "Individual.h"

Algorithm::Algorithm(KnapsackProblem* problem_instance, unsigned int iterations,
	unsigned int population_size, double mutation_probability,
	double crossover_possibility)
{
	//TODO: check for invalid values
	this->problem_instance = problem_instance;
	this->iterations = iterations;
	this->population_size = population_size;
	this->mutation_probability = mutation_probability;
	this->crossover_probability = crossover_possibility;

	this->population = new std::vector<Individual*>();
}

Algorithm::~Algorithm()
{
}

Individual* Algorithm::solve()
{
	return nullptr;
}