#include "pch.h"
#include "AlgorithmAction.h"
#include <iostream>

template<class T>
AlgorithmAction<T>::AlgorithmAction(Algorithm<T>* algorithm_instance)
{
	this->algorithm_instance = algorithm_instance;
}

template<class T>
void AlgorithmAction<T>::perform_action() const
{
	//TODO: memory leak here???
	Individual<T>* result = algorithm_instance->solve();
	std::cout << "Best found: " << result->to_string();
}

template<class T>
void AlgorithmAction<T>::perform_action(Individual<T>* result) const
{
	result = algorithm_instance->solve();
}



