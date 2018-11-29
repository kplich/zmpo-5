#include "pch.h"
#include "Individual.h"
#include <random>
#include <sstream>


Individual::Individual(int size)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<> distribution(0, 1);

	genotype = new bool[size];

	for(int i = 0; i < size; i++)
	{
		genotype[i] = distribution(generator);
	}
}

Individual::Individual(Individual& other)
{
	copy_from_another(other);
}

Individual::~Individual()
{
	delete[] genotype;
}

int Individual::evaluate_fitness(std::vector<std::pair<int, int>*>* items)
{
	int result;

	for(int i = 0; i < size; i++)
	{
		if(genotype[i])
		{
			result += items->at(i)->second;
		}
	}
	return result;
}

void Individual::mutate(double mutation_probability)
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
}

std::pair<Individual*, Individual*>* Individual::crossover(Individual* other, double crossover_probability)
{
	std::random_device device;
	std::mt19937 generator(device());

	Individual* first = new Individual(*this);
	Individual* second = new Individual(*other);

	if(std::generate_canonical<double, 10>(generator) < crossover_probability)
	{
		std::uniform_int_distribution<> distribution(1, size - 1);
		int cutting_point = distribution(generator);

		//swap genes for each gene, from the cutting point to the end
		for(int i = cutting_point; i < size; i++)
		{
			bool temp = first->genotype[i];
			first->genotype[i] = second->genotype[i];
			second->genotype[i] = temp;
		}
	}
	std::pair<Individual*, Individual*>	result(first, second);
}

std::string Individual::to_string()
{
	std::stringstream sstream;

	sstream << "my genotype:\n";

	for(int i = 0; i < size; i++)
	{
		sstream << genotype[i] << "  ";
	}

	return sstream.str();
}

Individual& Individual::operator=(const Individual& other)
{
	copy_from_another(other);
	return *this;
}

void Individual::copy_from_another(const Individual& other)
{
	//clean up old data
	delete[] this->genotype;

	//make room for new data
	this->size = other.size;
	this->genotype = new bool[size];

	//copy data
	for(int i = 0; i < size; i++)
	{
		genotype[i] = other.genotype[i];
	}
}
