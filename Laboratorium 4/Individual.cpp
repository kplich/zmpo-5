#include "pch.h"
#include "Individual.h"


Individual::Individual()
{
}

Individual::Individual(Individual& other)
{
	
}

Individual::~Individual()
{
}


int Individual::evaluate_fitness()
{
	// TODO: Add your implementation code here.
	return 0;
}

void Individual::mutate(double mutation_probability)
{
}

std::vector<Individual*> Individual::crossover(Individual * other)
{
	return std::vector<Individual*>();
}

Individual & Individual::operator=(const Individual & other)
{
	// TODO: insert return statement here
}

void Individual::copy(const Individual & other)
{
}
