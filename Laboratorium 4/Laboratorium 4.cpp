#include "pch.h"
#include "KnapsackProblem.h"
#include <string>
#include <fstream>
#include "Algorithm.h"
#include "Menu.h"
#include "AlgorithmAction.h"
#include "AbstractMenuItem.h"

Menu* getMainMenu();

int main()
{
	getMainMenu()->run();
}

Menu* getMainMenu()
{
	Menu* result = new Menu("main menu", "main");

	std::ifstream bool_file("problem-wojtek.txt");
	KnapsackProblem<bool>* bool_problem = new KnapsackProblem<bool>(&bool_file);
	Algorithm<bool>* bool_algorithm = new Algorithm<bool>(bool_problem, 15, 32, 0.01, 0.7);
	AbstractMenuItem* bool_solver = new Command("Solves the given problem as boolean.", "solve bool", result->get_path(), new AlgorithmAction<bool>(bool_algorithm), "no help here");

	std::ifstream int_file("problem-wojtek.txt");
	KnapsackProblem<int>* int_problem = new KnapsackProblem<int>(&int_file);
	Algorithm<int>* int_algorithm = new Algorithm<int>(int_problem, 15, 32, 0.01, 0.7);
	AbstractMenuItem* int_solver = new Command("Solves the given problem as integer.", "solve int", result->get_path(), new AlgorithmAction<int>(int_algorithm), "no help here");

	std::ifstream double_file("problem-wojtek.txt");
	KnapsackProblem<double>* double_problem = new KnapsackProblem<double>(&double_file);
	Algorithm<double>* double_algorithm = new Algorithm<double>(double_problem, 15, 32, 0.01, 0.7);
	AbstractMenuItem* double_solver = new Command("Solves the given problem as double.", "solve double", result->get_path(), new AlgorithmAction<double>(double_algorithm), "no help here");

	result->add_item(bool_solver);
	result->add_item(int_solver);
	result->add_item(double_solver);

	return result;
}