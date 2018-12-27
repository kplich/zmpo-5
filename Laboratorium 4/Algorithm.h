#pragma once
#include "KnapsackProblem.h"
#include "Individual.h"

/**
 * Class containing the logic of a genetic algorithm.
 */
class Algorithm
{
public:
	Algorithm(KnapsackProblem* problem_instance, int iterations = 20,
		int population_size = 100, double mutation_probability = 0.03,
		double crossover_probability = 0.6, int execution_time = 60);
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
	 * Stores state of the algorithm instance. If wrong parameters were passed,
	 * the instance won't be valid and won't be run.
	 */
	bool valid;

	/**
	 * Container for current population
	 */
	std::vector<Individual*>* population;

	/**
	 * Pointer to an instance of a problem we attempt to solve.
	 */
	KnapsackProblem* problem_instance;

	//TODO: currently unused!
	/**
	 * Number of iterations that the algorithm will perform
	 */
	int iterations;

	/**
	 * Number of individuals generated in each iteration.
	 */
	int population_size;

	/**
	 * Probability of random mutations of genotype.
	 */
	double mutation_probability;

	/**
	 * Probability of a crossover happening between any two individuals
	 * in a population.
	 */
	double crossover_probability;

	//TODO: two competing criteria: execution time and number of iterations
	int execution_time;

	void generate_population();

	void mutate_population();

	void print_population();

	void kill_population();

	Individual* find_best_in_iteration();
};

