#include "pch.h"
#include "KnapsackProblem.h"
#include <string>
#include <iostream>
#include "Individual.h"
#include "Algorithm.h"

void solve_problem();

int main()
{
	solve_problem();
}

void solve_problem()
{
	std::ifstream problem_file("problem1.txt");
	KnapsackProblem problem(&problem_file);

	std::ofstream results_file("results.txt");
	for (int pop = 4; pop < 256; pop *= 2)
	{
		results_file << pop << "\t";
		std::cout << "pop: " << pop << "\n";
		for (int i = 0; i < 100; i++)
		{
			Algorithm my_algorithm(&problem, 75, pop, 0.03, 0.5);
			Individual* found = my_algorithm.solve();

			//std::cout << found->to_string();
			std::cout << "fitness: " << problem.evaluate_fitness(found) << "\n";

			results_file << problem.evaluate_fitness(found) << "\t";
		}
		results_file << "\n";
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
