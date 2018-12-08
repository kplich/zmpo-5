#include "pch.h"
#include "Algorithm.h"
#include "Individual.h"
#include <random>
#include <iostream>

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

	this->population = new std::vector<Individual*>();
}

Algorithm::~Algorithm()
{
	delete population;
}

Individual* Algorithm::solve()
{
	int counter = iterations;
	Individual* best_ever = nullptr;

	if (problem_instance->is_valid()) {
		do
		{
			std::cout << "generation nr " << iterations - counter + 1 << "\n";

			generate_population();
			mutate_population();

			print_population();

			Individual* best_in_iteration = find_best_in_iteration();
			if (counter != iterations) {
				if (best_in_iteration->get_fitness() > best_ever->get_fitness())
				{
					//old best_ever is copied, because it's no longer necessary
					delete best_ever;
					//new best_ever is copied, because it has to outlive its generation
					best_ever = new Individual(*best_in_iteration);
				}
			}
			else
			{
				best_ever = new Individual(*best_in_iteration);
			}

			std::cout << "best in generation, fitness: " << best_in_iteration->get_fitness() << "\n\n";
			counter--;
		} while (counter > 0);

		kill_population();
	}
	else
	{
		//TODO: invalid problem instance
	}

	return best_ever;
}

void Algorithm::generate_population()
{
	if (population->empty())
	{
		for(int i = 0; i<population_size; i++)
		{
			Individual* temp = new Individual(problem_instance->get_number_of_items(), problem_instance);
			population->push_back(temp);
		}
	}
	else
	{
		//set up a new vector
		std::vector<Individual*>* new_population = new std::vector<Individual*>();

		//set up RNG
		std::random_device device;
		std::mt19937 generator(device());
		std::uniform_int_distribution<> distribution(0, population_size - 1);

		//generate new individuals until we reach desired population size
		while (new_population->size() < population_size)
		{
			//get four random individuals
			Individual* first = population->at(distribution(generator));
			Individual*second = population->at(distribution(generator));
			Individual*third = population->at(distribution(generator));
			Individual*fourth = population->at(distribution(generator));

			//assign them to roles of first parent and second parent
			Individual* first_parent;
			Individual* second_parent;
			if(first->get_fitness() >= second->get_fitness())
			{
				first_parent = first;
			}
			else
			{
				first_parent = second;
			}

			if(third->get_fitness() >= fourth->get_fitness())
			{
				second_parent = third;
			}
			else
			{
				second_parent = fourth;
			}

			//cross individuals over and get their children
			std::pair<Individual*, Individual*> children = first_parent->crossover(second_parent, crossover_probability);

			//evaluate children
			Individual* first_child = children.first;
			Individual* second_child = children.second;

			new_population->push_back(first_child);
			new_population->push_back(second_child);
		}

		kill_population();

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
		Individual* temp = population->at(i);
		temp->mutate(mutation_probability);
	}
}

void Algorithm::print_population()
{
	for (int i = 0; i < population->size(); i++)
	{
		Individual* temp = population->at(i);
		std::cout << temp->to_string();
	}

	std::cout << "\n";
}

void Algorithm::kill_population()
{
	for (int i = 0; i < population->size(); i++)
	{
		delete population->at(i);
	}

}

Individual* Algorithm::find_best_in_iteration()
{
	Individual* best = population->at(0);
	int max_fitness = population->at(0)->get_fitness();

	for(int i = 1; i < population_size; i++)
	{
		Individual* temp = population->at(i);
		if(temp->get_fitness() > max_fitness)
		{
			best = temp;
			max_fitness = temp->get_fitness();
		}
	}

	return best;
}


