#pragma once
#include <vector>
#include "KnapsackProblem.h"

//TODO: idea for later: maybe keep fitness as a variable?
//TODO: extract random generators

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
	explicit Individual(int size);

	Individual(Individual& other);

	~Individual();

	Individual& operator= (const Individual& other);

	//TODO: not a fan of passing these parameters explicitly
	/**
	 * \brief Evaluates the given individual in context of a particular
	 *		  Knapsack problem
	 * \param items vector of item sizes and values on which evaluation
	 *		  of an individual is based
	 * \param capacity maximum value that the fitness can have
	 * \return an integer representing fitness of an individual in context of a current problem.
	 */
	int evaluate_fitness(int capacity, std::vector<std::pair<int, int>*>* items);

	/**
	 * \brief Mutates every gene of the individual
	 * \param mutation_probability probability (same for every gene) that it
	 *		  will mutate
	 */
	void mutate(double mutation_probability);

	//TODO: implement an operator for that!
	//TODO: make it return a pointer to pair?
	/**
	 * \brief Performs a crossover with another individual.
	 * \param other Pointer to the other individual in the crossover
	 * \param crossover_probability probability that the individual will swap genes with one another
	 * \return a vector containing individuals that share their genes with
	 *		   both crossing-over individuals
	 */
	std::pair<Individual*, Individual*> crossover(Individual* other, double crossover_probability);

	std::string to_string();

private:
	/**
	 * Table encoding a solution to the problem.
	 */
	bool* genotype;

	/**
	 * Length of the table encoding the solution.
	 */
	int size;

	//TODO: fun idea: how about introducing random mutations EVERYTIME an individual is copied?
	//TODO: implement first, then implement constructors and operators
	void copy_from_another(const Individual& other);
};

