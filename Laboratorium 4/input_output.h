#pragma once
#pragma once
#include <string>
#include "AbstractMenuItem.h"
#include <map>

/**
 * Maximal size we allow a newly created or resized table to have.
 */
const int MAX_TABLE_SIZE = 999999;

/**
 * Greatest integer available.
 */
const int MIN_INTEGER = std::numeric_limits<int>::min();

/**
 * Smallest integer available.
 */
const int MAX_INTEGER = std::numeric_limits<int>::max();

/**
 * Helper method converting an integer to a string using a stringstream
 * @param number number to convert
 * @return number written as astring
 */
std::string int_to_string(int number);

/**
 * Helper method converting an string containing an integer to an actual integer.
 * @param string containing a number
 * @return an integer encoded by the given string
 */
int string_to_int(std::string string);

/**
 * Reads a line from command line.
 * @return a string containing input from user
 */
std::string get_user_input();

/**
 * Attempts to read an integer falling within a specified range from command line ONCE.
 * get_int_input(output, -5, 5) will accept any integer in range [-5, 5] (including bounds).
 * @param output reference to a variable that's going to hold the result
 * @param range_min lower bound of the range
 * @param range_max upper bound of the range
 * @bool false if the input wasn't a number or didn't fall within the specified range; true otherwise
 */
bool get_int_input(int& output, int range_min, int range_max);

/**
 * Attempts to read an integer falling within a specified range for a number of times.
 * @param range_min lower bound of the range
 * @param range_max upper bound of the range
 * @return an integer in range [range_min, range_max] (bounds included)
 */
int loop_until_valid_int(int range_min, int range_max);

/**
 * Prints a message communicating success or failure of an operation.
 * @param operation_succeeded boolean value indicating success of operation (true)
 */
void communicate_success(bool operation_succeeded);

void unknown_code();
/**
 * Helper method to simplify inserting VirtualMenuItems into a map
 * @param item_map map of items into which we insert the new item
 * @param menu_item item that we're inserting
 */
void insert_item_into_map(std::map<std::string, AbstractMenuItem*>* item_map, AbstractMenuItem* menu_item);