#pragma once
#include <vector>
#include "Individual.h"

class KnapsackProblem
{
public:
	KnapsackProblem(int capacity, int number_of_items, int* item_sizes, int* item_values);
	//TODO: file-based  constructor
	~KnapsackProblem();

	//TODO: translate an individual into a more readable solution
	//std::vector<int> individual_to_solution(Individual* individual);

private:
	int capacity;
	int number_of_items;

	//TODO: consider tying these entities together as a map
	int* item_sizes;
	int* item_values;
};

