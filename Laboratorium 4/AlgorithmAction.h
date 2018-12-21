#pragma once
#include "AbstractAction.h"
#include "Algorithm.h"

class AlgorithmAction : public AbstractAction
{
public:
	AlgorithmAction(Algorithm* algorithm_instance);

	void perform_action() const override;

	void perform_action(Individual* result) const;
private:
	Algorithm* algorithm_instance;
};
