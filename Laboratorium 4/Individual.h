#pragma once
#include <string>
#include "KnapsackProblem.h"

//forward declaration - to resolve a cyclic dependency between
//Individual class and KnapsackProblem class

/**
 * \brief Class encoding a possible solution to a problem. Equipped with
 *        methods allowing mutation and crossing with other individuals.
 */
class Individual
{
public:
	//explicit constructor doesn't allow implicit conversions
	/**
	 * Constructs an individual of a given size with
	 * a randomly initialized genotype.
	 * \param size length of the table encoding the solution (genotype)
	 */
	explicit Individual(int size, KnapsackProblem* problem_instance);

	Individual(Individual& other);

	~Individual();

	Individual& operator= (const Individual& other);

	Individual& operator+ (const Individual& other);

	void operator++();

	/**
	 * \brief Mutates every gene of the individual
	 * \param mutation_probability probability (same for every gene) that it
	 *		  will mutate
	 */
	void mutate(double mutation_probability);

	/**
	 * \brief Performs a crossover with another individual.
	 * \param other Pointer to the other individual in the crossover
	 * \param crossover_probability probability that the individual will swap genes with one another
	 * \return a vector containing individuals that share their genes with
	 *		   both crossing-over individuals
	 */
	std::pair<Individual*, Individual*> crossover(Individual* other, double crossover_probability);

	std::string to_string();

	int get_fitness();

private:
	KnapsackProblem* problem_instance;

	/**
	 * Table encoding a solution to the problem.
	 */
	bool* genotype;

	/**
	 * Length of the table encoding the solution.
	 */
	int size;

	/**
	 * Fitness of the given individual.
	 */
	int fitness;

	void copy_from_another(const Individual& other);
};

