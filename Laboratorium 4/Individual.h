#pragma once
#include <vector>
#include "KnapsackProblem.h"

//TODO: idea for later: maybe keep fitness as a variable?

/**
 * \brief Class encoding a possible solution to a problem. Equipped with
 *        methods allowing mutation and crossing with other individuals.
 */
class Individual
{
public:
	//TODO: probably deletable
	Individual();
	Individual(Individual& other);
	~Individual();

	Individual& operator= (const Individual& other);


	/**
	 * \brief Evaluates the given individual in context of a particular
	 *		  Knapsack problem
	 * \param problem_instance instance of the problem on which evaluation
	 *		  of an individual is based
	 * \return an integer representing fitness of an individual in context of a current problem.
	 */
	int evaluate_fitness(KnapsackProblem* problem_instance);

	/**
	 * \brief Mutates every gene of the individual
	 * \param mutation_probability probability (same for every gene) that it
	 *		  will mutate
	 */
	void mutate(double mutation_probability);

	//TODO: implement an operator for that!
	/**
	 * \brief Performs a crossover with another individual.
	 * \param other Pointer to the other individual in the crossover
	 * \return a vector containing individuals that share their genes with
	 *		   both crossing-over individuals
	 */
	std::vector<Individual*> crossover(Individual* other);
private:
	/**
	 * Table encoding a solution to the problem.
	 */
	bool* genotype;

	//TODO: fun idea: how about introducing random mutations EVERYTIME an individual is copied?
	//TODO: implement first, then implement constructors and operators
	void copy_from_another(const Individual& other);
};

