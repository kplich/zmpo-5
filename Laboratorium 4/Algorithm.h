#pragma once
#include "KnapsackProblem.h"
#include "Individual.h"

/**
 * Class containing the logic of a genetic algorithm.
 */
class Algorithm
{
public:
	//TODO: allow for default values of these parameters
	Algorithm(KnapsackProblem* problem_instance, unsigned int iterations,
		unsigned int population_size, double mutation_probability,
		double crossover_possibility);
	~Algorithm();

	/**
	 * \brief Main method of the class. Attempts to solve the problem
	 *		  by generating populations, crossing over and mutating
	 *		  individuals.
	 * \return pointer to an individual rated as best fitted after
	 *		   a given amount of iterations.
	 */
	Individual* solve();

private:
	/**
	 * Container for current population
	 */
	std::vector<std::pair<Individual*, int>*>* population;

	/**
	 * Pointer to an instance of a problem we attempt to solve.
	 */
	KnapsackProblem* problem_instance;

	/**
	 * Number of iterations that the algorithm will perform
	 */
	unsigned int iterations;

	/**
	 * Number of individuals generated in each iteration.
	 */
	unsigned int population_size;

	/**
	 * Probability of random mutations of genotype.
	 */
	double mutation_probability;

	/**
	 * Probability of a crossover happening between any two individuals
	 * in a population.
	 */
	double crossover_probability;

	void generate_population();
};

