#include "pch.h"
#include "KnapsackProblem.h"
#include <string>
#include <iostream>
#include "Individual.h"
#include "Algorithm.h"
#include "Menu.h"
#include "AlgorithmAction.h"
#include "AbstractMenuItem.h"

template<class T>
Menu* getMainMenu(Algorithm<T>* algorithm_instance);

void solve_with_stats();

void debugging();

int main()
{
	std::ifstream problem_file("problem-wojtek.txt");
	KnapsackProblem<double> problem(&problem_file);

	Algorithm<double> my_algorithm(&problem, 15, 32, 0.01, 0.7);
	Individual<double>* found = nullptr;

	if (found != nullptr) {
		std::cout << found->to_string();
	}

	Menu* menu = getMainMenu(&my_algorithm);
	menu->run();
}

template<class T>
Menu* getMainMenu(Algorithm<T>* algorithm_instance)
{
	Menu* result = new Menu("main menu", "main");

	AbstractMenuItem* algorithm_item = new Command("Solves the given knapsack problem.", "solve", result->get_path(), new AlgorithmAction<T>(algorithm_instance), "no help here");

	result->add_item(algorithm_item);

	return result;
}


void solve_with_stats()
{
	int min_iterations = 5;
	int max_iterations = 50;

	int repeats = 30;

	std::ifstream problem_file("problem-wojtek.txt");
	KnapsackProblem<bool> problem(&problem_file);

	std::ofstream results_file("results.txt");
	for (int iter = min_iterations; iter < max_iterations; iter +=2)
	{
		results_file << iter << "\t";
		std::cout << "pop: " << iter << "\n";
		for (int i = 0; i < repeats; i++)
		{
			Algorithm<bool> my_algorithm(&problem, iter, 32, 0.01, 0.5);
			Individual<bool>* found = my_algorithm.solve();

			std::cout << found->to_string();

			results_file << found->get_fitness() << "\t";
		}
		results_file << "\n";
	}
}

void debugging()
{
	
}