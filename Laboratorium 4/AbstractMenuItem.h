#pragma once
#include <string>
#include <list>

/**
 * Generic class for implementing a runnable menu item.
 * <b>Not mutable!</b>
 */
class AbstractMenuItem
{
public:
	static const char begin_and_end_string = '\'';

	AbstractMenuItem(std::string description, std::string command, std::string parent_path);

	/**
	 * Virtual destructor.
	 */
	virtual ~AbstractMenuItem();

	/**
	 * Virtual method that runs the menu or performs an action.
	 */
	//Pure virtual method makes the class abstract.
	virtual void run() = 0;

	/**
	 * Returns the command used to run the item.
	 * @return command used to run the item
	 */
	std::string get_command();

	/**
	 * Returns description of the item.
	 * @return string containing short description of the item
	 */
	std::string get_description();

	/**
	 * Returns the path from root menu to the item.
	 * @return description of the path to the item in the form
	 *  root_menu -> <intermediate items> -> command
	 */
	std::string get_path();

	/**
	 * Returns a textual representation of a menu item.
	 * @return textual representation of the menu item.
	 */
	virtual std::string to_string() = 0;

protected:
	/**
	 * Description of the menu or action performed.
	 */
	std::string description;

	/**
	 * Command that will be used to perform an action.
	 */
	std::string command;

	/**
	 * Path in the menu to an object.
	 */
	std::string path;
};

