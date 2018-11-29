#pragma once
#include "KnapsackProblem.h"

class Algorithm
{
public:

	Algorithm(KnapsackProblem* problem_instance, int iterations,
		int population_size, double mutation_probability,
		double crossover_possibility);
	~Algorithm();

	Individual* solve();

private:
	KnapsackProblem* problem_instance;

	int iterations;

	int population_size;
	double mutation_probability;
	double crossover_probability;
};

