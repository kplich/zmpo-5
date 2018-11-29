#pragma once
#include <vector>
#include "KnapsackProblem.h"

//TODO: idea for later: maybe keep fitness as a variable?

class Individual
{
public:
	Individual();
	Individual(Individual& other);
	~Individual();

	Individual& operator= (const Individual& other);

	int evaluate_fitness(KnapsackProblem* problem_instance);

	void mutate(double mutation_probability);

	std::vector<Individual*> crossover(Individual* other);
private:
	bool genotype[];

	//TODO: fun idea: how about introducing random mutations EVERYTIME an individual is copied?
	//TODO: implement first
	void copy(const Individual& other);
};

