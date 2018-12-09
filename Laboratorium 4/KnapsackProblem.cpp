#include "pch.h"
#include "KnapsackProblem.h"
#include <string>
#include <sstream>
#include "print_error.h"

const std::string FILE_NOT_OPENED_ERROR = "Couldn't open the file.";
const std::string UNKNOWN_IO_ERROR = "Unknown input/output error.";
const std::string INVALID_CAPACITY_ERROR = "Invalid capacity of the knapsack.";
const std::string INVALID_ITEM_SIZE_ERROR = "Invalid size of an item.";
const std::string INVALID_ITEM_VALUE_ERROR = "Invalid value of an item.";

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
	//we assume that loading will not succeed
	this->valid = false;

	//file might not be open
	if(!source_file->is_open())
	{
		print_error(FILE_NOT_OPENED_ERROR);
		return false;
	}

	int line_number = 1;

	//parse capacity
	std::string temp_line;
	std::getline(*source_file, temp_line);

	//TODO: more numbers might be declared here
	int capacity = std::stoi(temp_line);

	if (capacity <= 0)
	{
		print_error(INVALID_CAPACITY_ERROR, line_number);
		return false;
	}

	line_number++;

	//file might have been corrupted?
	if(!source_file->good())
	{
		print_error(UNKNOWN_IO_ERROR, line_number);
		return false;
	}

	//parse sizes and values
	std::vector<std::pair<int, int>*>* result = new std::vector<std::pair<int, int>*>();

	while (std::getline(*source_file, temp_line))
	{
		std::pair<int, int>* next_pair = get_size_value_pair(temp_line, line_number);;

		if (next_pair != nullptr) {
			result->push_back(next_pair);
		}

		line_number++;
	}

	if(!source_file->eof())
	{
		print_error(UNKNOWN_IO_ERROR);
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

std::pair<int, int>* KnapsackProblem::get_size_value_pair(std::string line, int line_number)
{
	int size = -1;
	int value = -1;

	std::stringstream stream(line);

	stream >> size;
	stream >> value;

	if (size <= 0)
	{
		print_error(INVALID_ITEM_SIZE_ERROR, line_number);
		return nullptr;
	}

	if (value <= 0)
	{
		print_error(INVALID_ITEM_VALUE_ERROR, line_number);
		return nullptr;
	}

	return new std::pair<int, int>(size, value);
}
