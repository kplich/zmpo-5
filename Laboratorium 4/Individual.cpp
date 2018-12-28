#include "pch.h"
#include "Individual.h"
#include <random>
#include <sstream>

template<>
Individual<bool>::Individual(int size, KnapsackProblem<bool>* problem_instance)
{
	this->problem_instance = problem_instance;
	this->size = size;

	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<> distribution(0, 1);

	genotype = new bool[size];

	for(int i = 0; i < size; i++)
	{
		genotype[i] = distribution(generator);
	}

	this->fitness = problem_instance->evaluate_fitness(genotype);
}

template <>
Individual<int>::Individual(int size, KnapsackProblem<int>* problem_instance)
{
	this->problem_instance = problem_instance;
	this->size = size;

	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<> distribution(0); //default max integer value

	genotype = new int[size];

	for(int i = 0; i < size; i++)
	{
		genotype[i] = distribution(generator);
	}

	this->fitness = problem_instance->evaluate_fitness(genotype);
}

template <>
Individual<double>::Individual(int size, KnapsackProblem<double>* problem_instance)
{
	this->problem_instance = problem_instance;
	this->size = size;

	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_real_distribution<> distribution(0, std::random_device::max());

	for(int i = 0; i < size; i++)
	{
		genotype[i] = distribution(generator);
	}

	this->fitness = problem_instance->evaluate_fitness(genotype);
}


template<class T>
Individual<T>::Individual(Individual<T>& other)
{
	copy_from_another(other);
}

template<class T>
Individual<T>::~Individual()
{
	delete[] genotype;
}

template<>
void Individual<bool>::mutate(double mutation_probability)
{
	std::random_device device;
	std::mt19937 generator(device());

	for(int i = 0; i < size; i++)
	{
		if(std::generate_canonical<double, 10>(generator) < mutation_probability)
		{
			genotype[i] = !genotype[i];
		}
	}

	fitness = problem_instance->evaluate_fitness(genotype);
}

template<>
void Individual<int>::mutate(double mutation_probability)
{
	std::random_device device;
	std::mt19937 generator(device());

	for (int i = 0; i < size; i++)
	{
		double random_temp = std::generate_canonical<double, 10>(generator);

		//here we just mutate
		if (random_temp < mutation_probability)
		{
			//here we decrease the gene
			if(random_temp < mutation_probability/2)
			{
				//only if it's greater than 0
				if(genotype[i] > 0)
				{
					genotype[i]--;
				}
			}
			//here we increase the gene
			else
			{
				genotype[i]++;
			}
			
		}
	}

	fitness = problem_instance->evaluate_fitness(genotype);
}

template<>
void Individual<double>::mutate(double mutation_probability)
{
	std::random_device device;
	std::mt19937 generator(device());

	for (int i = 0; i < size; i++)
	{
		double random_temp = std::generate_canonical<double, 10>(generator);

		//here we just mutate
		if (random_temp < mutation_probability)
		{
			//here we decrease the gene
			if (random_temp < mutation_probability / 2)
			{
				//only if it's greater than 0.5
				if (genotype[i] > 0.5)
				{
					genotype[i] -= 0.5;
				}
				else
				{
					genotype[i] = 0;
				}
			}
			//here we increase the gene
			else
			{
				genotype[i] += 0.5;
			}

		}
	}

	fitness = problem_instance->evaluate_fitness(genotype);
}

template<class T>
std::pair<Individual<T>*, Individual<T>*> Individual<T>::crossover(Individual<T>* other, double crossover_probability)
{
	std::random_device device;
	std::mt19937 generator(device());

	Individual<T>* first = new Individual<T>(*this);
	Individual<T>* second = new Individual<T>(*other);

	if(std::generate_canonical<double, 10>(generator) < crossover_probability)
	{
		std::uniform_int_distribution<> distribution(1, size - 1);
		int cutting_point = distribution(generator);

		//swap genes for each gene, from the cutting point to the end
		for(int i = cutting_point; i < size; i++)
		{
			T temp = first->genotype[i];
			first->genotype[i] = second->genotype[i];
			second->genotype[i] = temp;
		}
	}

	first->fitness = problem_instance->evaluate_fitness(genotype);
	second->fitness = problem_instance->evaluate_fitness(genotype);

	std::pair<Individual<T>*, Individual<T>*> result(first, second);
	return result;
}

template<class T>
std::string Individual<T>::to_string()
{
	std::stringstream sstream;

	for(int i = 0; i < size; i++)
	{
		sstream << genotype[i] << "  ";
	}

	sstream << ", fitness: " << fitness << "\n";

	return sstream.str();
}

template<class T>
int Individual<T>::get_fitness()
{
	return fitness;
}

template<class T>
Individual<T>& Individual<T>::operator=(const Individual<T>& other)
{
	copy_from_another(other);
	return *this;
}

template<class T>
Individual<T>& Individual<T>::operator+(const Individual<T>& other)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<> distribution(1, size - 1);

	Individual<T>* child = new Individual<T>(*this);

	int cutting_point = distribution(generator);

	//swap genes for each gene, from the cutting point to the end
	for (int i = cutting_point; i < size; i++)
	{
		child->genotype[i] = other.genotype[i];
	}

	child->fitness = problem_instance->evaluate_fitness(this->genotype);

	return *child;
}

template<class T>
void Individual<T>::operator++()
{
	this->mutate(0.5);
}

template<class T>
void Individual<T>::copy_from_another(const Individual<T>& other)
{
	//clean up old data
	delete[] this->genotype;

	//make room for new data
	this->problem_instance = other.problem_instance;
	this->size = other.size;
	this->fitness = other.fitness;
	this->genotype = new T[size];

	//copy data
	for(int i = 0; i < size; i++)
	{
		genotype[i] = other.genotype[i];
	}
}

template class Individual<bool>;
template class Individual<int>;
template class Individual<double>;