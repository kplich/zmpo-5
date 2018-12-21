#pragma once
#include <list>

/**
 * Class simplifying parsing a string and keeping track of position in the string.
 */
class ParsingStack
{
public:
	ParsingStack(std::string string);
	~ParsingStack();

	/**
	 * Peeks the character at the top of the string.
	 * @param result reference to the peeked character
	 * @return true if peeking the character was possible and succeeded, false otherwise
	 */
	bool peek(char& result);

	/**
	 * Method for popping a character from the top of the stack to a variable.
	 * @param result reference to character containing the popped character
	 * (content undefined when method returns false!)
	 * @return true if popping the character was possible, false otherwise
	 */
	bool pop_one(char& result);

	/**
	 * Pop a character from the string and check if it's equal to an expected character
	 */
	bool pop_equal_to(char expected);

	/**
	 * Extracts a string of characters until given character has been found.
	 * After exiting the method, the stack doesn't contain the ending character.
	 * @param result reference to a string containing all the characters popped until ending character has been found
	 * (the returned string doesn't contain the ending character) (content undefined when method returns false!)
	 * @param ending_character character that's supposed to terminate popping the characters
	 * @return true if extraction succeeded, false otherwise
	 */
	bool pop_until_char_found(std::string& result, char ending_character);

	/**
	 * Returns current position in the input string.
	 * @return current position in the input string
	 */
	int get_position();

	/**
	 * @return true, if there are no elements in the stack, false otherwise
	 */
	bool empty();

private:
	/**
	 * Source of chars.
	 */
	std::list<char>* source;

	/**
	 * Number indicating position in the string - number of the last popped character.
	 */
	int position_counter;
};
