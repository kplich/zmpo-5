#include "pch.h"
#include "Algorithm.h"
#include "Individual.h"
#include <random>

Algorithm::Algorithm(KnapsackProblem* problem_instance, unsigned int iterations,
	unsigned int population_size, double mutation_probability,
	double crossover_possibility)
{
	//TODO: check for invalid values
	this->problem_instance = problem_instance;
	this->iterations = iterations;
	this->population_size = population_size;
	this->mutation_probability = mutation_probability;
	this->crossover_probability = crossover_possibility;

	this->population = new std::vector<std::pair<Individual*, int>*>();
}

Algorithm::~Algorithm()
{
}

Individual* Algorithm::solve()
{
	int counter = iterations;
	std::pair<Individual*, int>* best_in_iteration;

	do
	{
		generate_population();
		mutate_population();
		best_in_iteration = find_best_in_population();
		counter--;
	} while (counter > 0);

	return best_in_iteration->first;
}

void Algorithm::generate_population()
{
	if (population->empty())
	{
		for(int i = 0; i<population_size; i++)
		{
			Individual* temp = new Individual(problem_instance->get_number_of_items());
			int temp_fitness = problem_instance->evaluate_fitness(temp);
			population->push_back(new std::pair<Individual*, int>(temp, temp_fitness));
		}
	}
	else
	{
		//set up a new vector
		std::vector<std::pair<Individual*, int>*>* new_population = new std::vector<std::pair<Individual*, int>*>();

		//set up RNG
		std::random_device device;
		std::mt19937 generator(device());
		std::uniform_int_distribution<> distribution(0, population_size - 1);

		//generate new individuals until we reach desired population size
		while (new_population->size() < population_size)
		{
			//get four random individuals
			std::pair<Individual*, int>* first = population->at(distribution(generator));
			std::pair<Individual*, int>* second = population->at(distribution(generator));
			std::pair<Individual*, int>* third = population->at(distribution(generator));
			std::pair<Individual*, int>* fourth = population->at(distribution(generator));

			//assign them to roles of first parent and second parent
			Individual* first_parent;
			Individual* second_parent;
			if(first->second >= second->second)
			{
				first_parent = first->first;
			}
			else
			{
				first_parent = second->first;
			}

			if(third->second >= fourth->second)
			{
				second_parent = third->first;
			}
			else
			{
				second_parent = fourth->first;
			}

			//cross individuals over and get their children
			std::pair<Individual*, Individual*> children = first_parent->crossover(second_parent, crossover_probability);

			//evaluate children
			std::pair<Individual*, int>* first_child = new std::pair<Individual*, int>(children.first, problem_instance->evaluate_fitness(children.first));
			std::pair<Individual*, int>* second_child = new std::pair<Individual*, int>(children.second, problem_instance->evaluate_fitness(children.second));

			new_population->push_back(first_child);
			new_population->push_back(second_child);
		}

		//deallocate old population
		for(int i = 0; i < population->size(); i++)
		{
			//delete the individual
			delete population->at(i)->first;

			//delete its pair
			delete population->at(i);
		}

		//deallocate the containter
		delete population;

		//and let the new one take its place
		population = new_population;
	}
}

void Algorithm::mutate_population()
{
	for(int i = 0; i < population_size; i++)
	{
		population->at(i)->first->mutate(mutation_probability);
	}
}

std::pair<Individual*, int>* Algorithm::find_best_in_population()
{
	int max_fitness = population->at(0)->second;
	std::pair<Individual*, int>* best = population->at(0);

	for(int i = 1; i < population_size; i++)
	{
		std::pair<Individual*, int>* temp = population->at(i);
		if(temp->second > max_fitness)
		{
			best = temp;
			max_fitness = temp->second;
		}
	}

	return best;
}


