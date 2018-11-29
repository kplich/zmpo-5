#include "pch.h"
#include "KnapsackProblem.h"
#include <string>


KnapsackProblem::KnapsackProblem(unsigned int capacity, std::vector<std::pair<unsigned int, unsigned int>*>* items)
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
		items = new std::vector<std::pair<unsigned int, unsigned int>*>();
		valid = false;
	}
}

unsigned int KnapsackProblem::get_number_of_items()
{
	return items->size();
}

bool KnapsackProblem::is_valid()
{
	return valid;
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
	unsigned int capacity = std::stoi(first_line);

	//parse sizes and values
	std::vector<std::pair<unsigned int, unsigned int>*>* result = new std::vector<std::pair<unsigned int, unsigned int>*>();

	unsigned int temp_size;
	unsigned int temp_value;
	do
	{
		//TODO: maybe better to read this line by line?
		*source_file >> temp_size >> temp_value;
		std::pair<unsigned int, unsigned int>* next_pair = new std::pair<unsigned int, unsigned int>(temp_size, temp_value);
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
