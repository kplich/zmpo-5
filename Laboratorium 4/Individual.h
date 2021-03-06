#pragma once
#include <string>
#include "KnapsackProblem.h"

//forward declaration - to resolve a cyclic dependency between
//Individual class and KnapsackProblem class

/**
 * \brief Class encoding a possible solution to a problem. Equipped with
 *        methods allowing mutation and crossing with other individuals.
 */
template<class T>
class Individual
{
public:
	//explicit constructor doesn't allow implicit conversions
	/**
	 * Constructs an individual of a given size with
	 * a randomly initialized genotype.
	 * \param size length of the table encoding the solution (genotype)
	 */
	explicit Individual(int size, KnapsackProblem<T>* problem_instance, double mutation_probability);

	Individual(Individual<T>& other);

	~Individual();

	Individual<T>& operator= (const Individual<T>& other);

	Individual<T>& operator+ (const Individual<T>& other);

	void operator++(int);

	/**
	 * \brief Mutates every gene of the individual
	 */
	void mutate();

	/**
	 * \brief Performs a crossover with another individual.
	 * \param other Pointer to the other individual in the crossover
	 * \param crossover_probability probability that the individual will swap genes with one another
	 * \return a vector containing individuals that share their genes with
	 *		   both crossing-over individuals
	 */
	std::pair<Individual<T>*, Individual<T>*> crossover(Individual<T>* other, double crossover_probability);

	std::string to_string();

	int get_fitness();

private:
	KnapsackProblem<T>* problem_instance;

	double mutation_probability;

	/**
	 * Table encoding a solution to the problem.
	 */
	T* genotype;

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