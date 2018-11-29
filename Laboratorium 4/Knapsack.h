#pragma once
class Knapsack
{
public:
	Knapsack();
	Knapsack(int capacity, int number_of_items, int* item_sizes, int* item_values);
	//TODO: file-based  constructor
	~Knapsack();

private:
	int capacity;
	int number_of_items;

	//TODO: consider tying these entities together as a map
	int* item_sizes;
	int* item_values;
};

