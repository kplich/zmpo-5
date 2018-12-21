#include "pch.h"
#include "ParsingStack.h"
#include <string>
#include <iostream>

ParsingStack::ParsingStack(std::string string)
{
	//deallocated in destructor
	this->source = new std::list<char>(string.begin(), string.end());
	this->position_counter = 0;
}

ParsingStack::~ParsingStack()
{
	delete source;
}

bool ParsingStack::peek(char& result)
{
	if(source->empty())
	{
		return false;
	}
	else
	{
		result = source->front();
		return true;
	}
}

bool ParsingStack::pop_one(char& result)
{
	if(source->empty())
	{
		return false;
	}
	else
	{
		result = source->front();
		source->pop_front();

		++position_counter;

		return true;
	}
}

//this method is kind of useless, bc false could be both an error and simply a mismatch
bool ParsingStack::pop_equal_to(char expected)
{
	char found;

	if(pop_one(found))
	{
		return (found == expected);
	}
	else
	{
		return false;
	}
}

bool ParsingStack::pop_until_char_found(std::string& result, char ending_character)
{
	result = "";
	char current_top;

	//the loop is executed until it's possible to extract a character from the stack
	while (pop_one(current_top))
	{
		if (current_top != ending_character)
		{
			result += current_top;
		}
		else
		{
			return true;
		}
	}

	return false;
}

int ParsingStack::get_position()
{
	return position_counter;
}

bool ParsingStack::empty()
{
	return source->empty();
}




