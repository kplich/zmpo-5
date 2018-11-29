#pragma once
#include <vector>

class Individual
{
public:
	Individual();
	Individual(Individual& other);
	~Individual();

	Individual& operator= (const Individual& other);

	//TODO: add problem instance to parameter list
	int evaluate_fitness();

	void mutate(double mutation_probability);

	std::vector<Individual*> crossover(Individual* other);
private:
	bool genotype[];

	//TODO: fun idea: how about introducing random mutations EVERYTIME an individual is copied?
	//TODO: implement first
	void copy(const Individual& other);
};

