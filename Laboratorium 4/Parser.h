#pragma once
#include "Menu.h"
#include "../ParsingStack/ParsingStack.h"

/**
 * Class parsing Menu items saved to string.
 */
class Parser
{
public:

	/**
	 * Parser only needs to be constructed from an input string.
	 */
	Parser(std::string input);

	~Parser();

	/**
	 * This method parses the given string, representing it as a stack.
	 * @return pointer to a menu constructed from the input string
	 * or null pointer if parsing failed
	 */
	Menu* parse();

private:
	/**
	 * String represented as a stack.
	 */
	ParsingStack* source;

	/**
	 * Method used to parse children of some menu - regardless of class they are
	 * @param root pointer to a parent item
	 * @param parent_path path of a parent item
	 * @return pointer to a menu item parsed from current position of a string.
	 *		   or a null pointer if parsing fails
	 */
	AbstractMenuItem* parse_item(Menu* root, std::string parent_path);

	/**
	 * Method for parsing a menu.
	 * @param root pointer to a parent item
	 * @param parent_path path of a parent item
	 * @return pointer to a menu parsed from current position of a string
	 *		   or a null pointer if parsing fails
	 */
	Menu* parse_menu(Menu* root, std::string parent_path);

	/**
	 * Method for parsing a command.
	 * @param parent_path path of a parent item
	 * @return pointer to a command parsed from current position of a string
	 *		   or a null pointer if parsing fails
	 */
	Command* parse_command(std::string parent_path);

	/**
	 * Helper method for parsing first two parts of a menu - description and command.
	 * @param root pointer to a parent item
	 * @param parent_path path of a parent item
	 * @return pointer to a menu parsed from current position of a string
	 *		   or a null pointer if parsing fails
	 */
	Menu* parse_beginning_of_menu(Menu* root, std::string parent_path);

	/**
	 * Helper method for extracting a string delimited by certain characters (apostrophes (') by default)
	 * @param result reference to a string containing the resulting string (without the delimiters)
	 * @return true if string was extracted successfully, false otherwise (e. g. in case of a unclosed string ('...)
	 */
	bool extract_string(std::string& result);

	bool extract_number(int& result);

	/**
	 * Helper method for parsing a char and checking if it matches the expected char.
	 * When the characters don't match, the method also signals the mismatch to the user.
	 * @param expected character to match against
	 * @return true if the parsed character matched the expected one, false otherwise
	 */
	bool parse_char(char expected);

	/**
	 * Helper method for signalling a parsing error where there was a clear mismatch between an expected and found character.
	 * @param expected charater that was expected
	 * @param found character found
	 */
	void parsing_error(char expected, char found);

	void parsing_error(std::string expected, char found);

	/**
	 * Helper method for signalling other errors with causes different than a character mismatch.
	 * @param message message about the error
	 */
	void parsing_error(std::string message);

	/**
	 * Helper method signalling that the string has ended too early.
	 */
	void end_of_string_error();

};

