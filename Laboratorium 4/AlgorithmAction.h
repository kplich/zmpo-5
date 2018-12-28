#pragma once
#include "AbstractAction.h"
#include "Algorithm.h"

template<class T>
class AlgorithmAction : public AbstractAction
{
public:
	AlgorithmAction(Algorithm<T>* algorithm_instance);

	void perform_action() const override;

	void perform_action(Individual<T>* result) const;
private:
	Algorithm<T>* algorithm_instance;
};
