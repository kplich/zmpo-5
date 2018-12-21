#include "pch.h"
#include "AlgorithmAction.h"
#include <iostream>

AlgorithmAction::AlgorithmAction(Algorithm* algorithm_instance)
{
	this->algorithm_instance = algorithm_instance;
}

void AlgorithmAction::perform_action() const
{
	//TODO: memory leak here???
	Individual* result = algorithm_instance->solve();
	std::cout << "Best found: " << result->to_string();
}

void AlgorithmAction::perform_action(Individual* result) const
{
	result = algorithm_instance->solve();
}



