#include "pch.h"
#include "Algorithm.h"
#include "Individual.h"
#include <random>
#include <iostream>
#include "print_error.h"
#include <chrono>

const std::string INVALID_ALGORITHM_INSTANCE = "Can't run the algorithm.\nInvalid algorithm instance.";
const std::string INVALID_PROBLEM_INSTANCE = "Invalid problem instance used.";
const std::string INVALID_ITERATIONS_COUNT = "Invalid number of iterations passed.";
const std::string INVALID_POPULATION_SIZE = "Invalid population size passed.";
const std::string INVALID_MUTATION_PROBABILITY = "Mutation probability out of range.";
const std::string INVALID_CROSSOVER_PROBABILITY = "Crossover probability out of range.";
const std::string INVALID_EXECUTION_TIME = "Invalid execution time.";

template<class T>
Algorithm<T>::Algorithm(KnapsackProblem<T>* problem_instance, int iterations,
	int population_size, double mutation_probability,
	double crossover_probability, int execution_time)
{
	this->valid = true;

	if(!problem_instance->is_valid() || problem_instance == nullptr)
	{
		print_error(INVALID_PROBLEM_INSTANCE);
		this->valid = false;
	}

	if(iterations <= 0)
	{
		print_error(INVALID_ITERATIONS_COUNT);
		this->valid = false;
	}

	if(population_size <= 0)
	{
		print_error(INVALID_POPULATION_SIZE);
		this->valid = false;
	}

	if(mutation_probability < 0 || mutation_probability > 1)
	{
		print_error(INVALID_MUTATION_PROBABILITY);
		this->valid = false;
	}

	if (crossover_probability < 0 || crossover_probability > 1)
	{
		print_error(INVALID_CROSSOVER_PROBABILITY);
		this->valid = false;
	}

	if (execution_time <= 0)
	{
		print_error(INVALID_EXECUTION_TIME);
		this->valid = false;
	}

	this->problem_instance = problem_instance;
	this->iterations = iterations;
	this->population_size = population_size;
	this->mutation_probability = mutation_probability;
	this->crossover_probability = crossover_probability;
	this->execution_time = execution_time;

	this->population = new std::vector<Individual<T>*>();
}

template<class T>
Algorithm<T>::~Algorithm()
{
	delete population;
}

template<class T>
Individual<T>* Algorithm<T>::solve()
{
	const std::chrono::steady_clock::time_point beginning = std::chrono::steady_clock::now();
	std::chrono::duration<double> time_passed;
	int counter = iterations;
	Individual<T>* best_ever = nullptr;

	if (!this->valid) {
		print_error(INVALID_ALGORITHM_INSTANCE);
		return nullptr;
	}

	do
	{
		this->generate_population();
		this->mutate_population();

		this->print_population();

		Individual<T>* best_in_iteration = find_best_in_iteration();
		if (counter != iterations) {
			if (best_in_iteration->get_fitness() > best_ever->get_fitness())
			{
				//old best_ever is copied, because it's no longer necessary
				delete best_ever;
				//new best_ever is copied, because it has to outlive its generation
				best_ever = new Individual<T>(*best_in_iteration);
			}
		}
		else
		{
			best_ever = new Individual<T>(*best_in_iteration);
		}

		std::cout << "best in generation, fitness: " << best_in_iteration->get_fitness() << "\n\n";
		counter--;

		time_passed = std::chrono::steady_clock::now() - beginning;
	} while (time_passed.count() < execution_time);

	kill_population();

	this->valid = false;

	return best_ever;
}

template<class T>
void Algorithm<T>::generate_population()
{
	if (population->empty())
	{
		for(int i = 0; i<population_size; i++)
		{
			Individual<T>* temp = new Individual<T>(problem_instance->get_number_of_items(), problem_instance, mutation_probability);
			population->push_back(temp);
		}
	}
	else
	{
		//set up a new vector
		std::vector<Individual<T>*>* new_population = new std::vector<Individual<T>*>();

		//set up RNG
		std::random_device device;
		std::mt19937 generator(device());
		std::uniform_int_distribution<> distribution(0, population_size - 1);


		//generate new individuals until we reach desired population size
		while (new_population->size() < population_size)
		{
			//get two random individuals
			Individual<T> first = *(population->at(distribution(generator)));
			Individual<T> second = *(population->at(distribution(generator)));

			//cross individuals over and get their child
			Individual<T>* child = &(first + second);

			new_population->push_back(child);
		}

		kill_population();

		//deallocate the containter
		delete population;

		//and let the new one take its place
		population = new_population;
	}
}

template<class T>
void Algorithm<T>::mutate_population()
{
	for(int i = 0; i < population_size; i++)
	{
		( *(population->at(i)) )++;
	}
}

template<class T>
void Algorithm<T>::print_population()
{
	for (int i = 0; i < population->size(); i++)
	{
		Individual<T>* temp = population->at(i);
		std::cout << temp->to_string();
	}

	std::cout << "\n";
}

template<class T>
void Algorithm<T>::kill_population()
{
	for (int i = 0; i < population->size(); i++)
	{
		delete population->at(i);
	}

}

template<class T>
Individual<T>* Algorithm<T>::find_best_in_iteration()
{
	Individual<T>* best = population->at(0);
	int max_fitness = population->at(0)->get_fitness();

	for(int i = 1; i < population_size; i++)
	{
		Individual<T>* temp = population->at(i);
		if(temp->get_fitness() > max_fitness)
		{
			best = temp;
			max_fitness = temp->get_fitness();
		}
	}

	return best;
}

template class Algorithm<bool>;
template class Algorithm<int>;
template class Algorithm<double>;