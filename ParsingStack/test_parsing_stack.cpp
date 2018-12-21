#include "ParsingStack.h"
#include <iostream>

int main()
{
	ParsingStack test_stack("xxdd'whatever'is'here");

	std::string test = test_stack.pop_until_char_found('\'');
}
