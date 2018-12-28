#pragma once
#include <vector>
#include <map>
#include <fstream>

/**
 * \brief Class defining the knapsack problem.
 * 
 * Items aren't stored in map, because ordering of items is
 * an important issue that can significantly alter the solution quality.
 */
template<class T>
class KnapsackProblem
{
public:
	KnapsackProblem(std::ifstream* source_file);
	KnapsackProblem(int capacity, std::vector<std::pair<int, int>*>* items);
	~KnapsackProblem();

	int get_number_of_items();

	/**
	 * Checks for validity of instance.
	 * \return true if the instance is valid and can be used,
	 *		   false if an error occured while reading it from a file
	 *		   or if there are no items declared
	 */
	bool is_valid();

	std::string to_string();

	double evaluate_fitness(T* genotype);

private:
	/**
	 * Maximal size of items that can be chosen.
	 */
	int capacity;

	/**
	 * Validity of an instance.
	 */
	bool valid;

	/**
	 * Vector of (item_size, item_value) pairs representing items
	 * to choose from. Size of this vector corresponds to the number
	 * of items to choose from.
	 */
	std::vector<std::pair<int, int>*>* items;

	/**
	 * \brief Method attempting to load data for the problem from file.
	 * \param source_file pointer to an opened stream from which the data
	 *		  can be read. After finishing the reading the stream isn't closed.
	 * \return true if reading is successful, false if an error occured.
	 */
	bool load_from_file(std::ifstream* source_file);

	std::pair<int, int>* get_size_value_pair(std::string line, int line_number);
};

