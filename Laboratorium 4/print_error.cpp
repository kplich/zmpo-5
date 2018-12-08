#include "pch.h"
#include "print_error.h"
#include <iostream>

void print_error(std::string message, int line)
{
	if(line > 0)
	{
		std::cout << "Error in line " << line << ":\n";
	}

	std::cout << message << "\n";
}
