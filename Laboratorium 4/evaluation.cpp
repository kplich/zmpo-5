#include "pch.h"
#include "evaluation.h"

int evaluate_fitness(Individual* individual, KnapsackProblem* problem_instance)
{
	int value = 0;
	int size = 0;

	for (int i = 0; i < problem_instance->get_number_of_items(); i++)
	{
		if (individual->genotype[i])
		{
			size += problem_instance->items->at(i)->first;
			value += problem_instance->items->at(i)->second;
		}
	}

	if (size > problem_instance->capacity)
	{
		value = 0;
	}

	return value;
}
