#pragma once
#include <vector>
#include "Individual.h"
#include <map>

/**
 * Class defining the knapsack problem.
 * 
 * Items aren't stored in map, because ordering of items is
 * an important issue that can significantly alter the solution quality.
 */
class KnapsackProblem
{
public:
	KnapsackProblem(int capacity, int number_of_items, int* item_sizes, int* item_values);
	//TODO: file-based  constructor
	~KnapsackProblem();

	//TODO: translate an individual into a more readable solution
	//std::vector<int> individual_to_solution(Individual* individual);

private:
	/**
	 * Maximal size of items that can be chosen.
	 */
	int capacity;

	/**
	 * Number of items to choose from. (size of tables below)
	 */
	int number_of_items;

	//TODO: consider tying these entities together as a map
	int* item_sizes;
	int* item_values;

	//TODO: which representation to choose?
	/**
	 * Vector of (item_size, item_value) pairs representing items
	 * to choose from.
	 */
	std::vector<std::pair<int, int>> items;
};

