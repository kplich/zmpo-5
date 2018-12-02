#include "pch.h"
#include "KnapsackProblem.h"
#include <string>
#include <sstream>


KnapsackProblem::KnapsackProblem(int capacity, std::vector<std::pair<int, int>*>* items)
{
	this->capacity = capacity;
	this->items = items;

	if(capacity == 0 || items->size() == 0)
	{
		this->valid = false;
	}
}

KnapsackProblem::~KnapsackProblem()
{
	for (int i = 0; i < items->size(); i++)
	{
		delete items->at(i);
	}

	delete items;
}

KnapsackProblem::KnapsackProblem(std::ifstream* source_file)
{
	if (!load_from_file(source_file))
	{
		capacity = 0;
		items = new std::vector<std::pair<int, int>*>();
		valid = false;
	}
}

int KnapsackProblem::get_number_of_items()
{
	return items->size();
}

bool KnapsackProblem::is_valid()
{
	return valid;
}

std::string KnapsackProblem::to_string()
{
	std::stringstream sstream;

	sstream << "Knapsack capacity: " << capacity << "\n";

	for(int i = 0; i<get_number_of_items(); i++)
	{
		sstream << "item " << i;
		sstream << "\tsize: " << items->at(i)->first;
		sstream << "\tvalue: " << items->at(i)->second << "\n";
	}

	return sstream.str();
}

bool KnapsackProblem::load_from_file(std::ifstream* source_file)
{
	if(!source_file->is_open())
	{
		//TODO: file not opened error
		return false;
	}

	//parse capacity
	std::string first_line;
	std::getline(*source_file, first_line);

	if(!source_file->good())
	{
		//TODO: input output error
		return false;
	}

	//TODO: more numbers might be declared here
	int capacity = std::stoi(first_line);

	//parse sizes and values
	std::vector<std::pair<int, int>*>* result = new std::vector<std::pair<int, int>*>();

	int temp_size;
	int temp_value;
	do
	{
		//TODO: maybe better to read this line by line?
		//TODO: also check for negative values!
		//TODO: sensitive to newlines at the end of the file!
		*source_file >> temp_size >> temp_value;
		std::pair<int, int>* next_pair = new std::pair<int, int>(temp_size, temp_value);
		result->push_back(next_pair);
	} while (source_file->good()); //TODO: is that a proper way to loop a stream?

	if(!source_file->eof())
	{
		//TODO: input output error
		//unknown input output error, discard everything we read
		for(int i = 0; i<result->size(); i++)
		{
			delete result->at(i);
		}

		delete result;

		return false;
	}

	//no failures, we can assign what we read
	this->capacity = capacity;
	this->items = result;
	this->valid = true;

	return true;
}
