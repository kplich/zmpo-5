#include "pch.h"
#include "Menu.h"
#include <iostream>
#include <iterator>
#include "input_output.h"
#include <fstream>
#include "Parser.h"
#include "special_actions.h"
#include <sstream>

static const std::string available_items = "Available options:";
static const std::string no_item_found = "No option with given command found.";


Menu::Menu(std::string description, std::string command, Menu* root_menu, std::string parent_path):
	AbstractMenuItem(description, command, parent_path)
{
	if (root_menu == nullptr)
	{
		this->root_menu = this;
	}
	else
	{
		this->root_menu = root_menu;
	}

	//this is deallocated in Menu destructor
	this->item_map = new std::map<std::string, AbstractMenuItem*>();

	//this is also deallocated in Menu destructor
	this->return_item = new Command(
		return_item_description,
		return_item_command,
		this->get_path(),
		new ReturnAction(), //this is deallocated in Command destructor
		return_item_help
	);

	//deallocated in Menu destructor
	this->search_item = new Command(
		search_item_description,
		search_item_command,
		this->get_path(),
		new SearchAction(this->root_menu), //deallocated in Command destructor
		search_item_help
	);

	//deallocated in Menu destructor
	this->help_item = new Command(
		help_item_description,
		help_item_command,
		this->get_path(),
		new HelpAction(this->item_map), //deallocated in Command destructor
		help_item_help
	);
}


Menu::Menu(std::map<std::string, AbstractMenuItem*>* item_map, std::string description, std::string command, Menu* root_menu, std::string parent_path):
	AbstractMenuItem(description, command, parent_path)
{
	if (root_menu == nullptr)
	{
		this->root_menu = this;
	}
	else
	{
		this->root_menu = root_menu;
	}

	this->item_map = item_map;

	//this is also deallocated in Menu destructor
	this->return_item = new Command(
		return_item_description,
		return_item_command,
		this->get_path(),
		new ReturnAction(), //this is deallocated in Command destructor
		return_item_help
	);

	//deallocated in Menu destructor
	this->search_item = new Command(
		search_item_description,
		search_item_command,
		this->get_path(),
		new SearchAction(this->root_menu), //deallocated in Command destructor
		search_item_help
	);

	//deallocated in Menu destructor
	this->help_item = new Command(
		help_item_description,
		help_item_command,
		this->get_path(),
		new HelpAction(this->item_map), //deallocated in Command destructor
		help_item_help
	);
}

Menu::~Menu()
{
	//deallocate special items
	delete return_item;
	delete search_item;
	delete help_item;

	//deallocate all items in the map and the map itself
	std::map<std::string, AbstractMenuItem*>::iterator deleting_iterator = item_map->begin();

	while(deleting_iterator != item_map->end())
	{
		delete deleting_iterator->second;
		++deleting_iterator;
	}
	item_map->clear();
	delete item_map;
}

void Menu::print_options()
{
	std::cout << "\n" << available_items << "\n";

	std::map<std::string, AbstractMenuItem*>::iterator temp_iterator = item_map->begin();

	for ( ; temp_iterator != item_map->end(); ++temp_iterator)
	{
		std::cout << temp_iterator->second->get_description() << ":\t" << temp_iterator->first << "\n";
	}
	std::cout << "\n";
}

AbstractMenuItem* Menu::choose_option()
{
	std::string user_input = get_user_input();
	AbstractMenuItem* found_item = nullptr;

	if (user_input == return_item_command)
	{
		found_item = return_item;
	}
	if (user_input == search_item_command)
	{
		found_item = search_item;
	}
	if (user_input == help_item_command)
	{
		found_item = help_item;
	}

	std::map<std::string, AbstractMenuItem*>::iterator find_iterator = item_map->find(user_input);
	if(find_iterator != item_map->end())
	{
		found_item = find_iterator->second;
	}
	
	return found_item;
}

void Menu::search_for_command(std::string command_name, std::vector<std::string>* found_paths)
{
	std::map<std::string, AbstractMenuItem*>::iterator find_iterator = item_map->find(command_name);

	if (find_iterator != item_map->end())
	{
		found_paths->push_back(find_iterator->second->get_path());
	}

	std::map<std::string, AbstractMenuItem*>::iterator search_deeper_iterator = item_map->begin();

	while (search_deeper_iterator != item_map->end())
	{
		//from Wikipedia: "(...) the result of a static_cast from a pointer of a virtual base class to a pointer of a derived class is undefined."
		//we don't know, if the pointer from iterator points to a menu or a command,
		//so we use a dynamic conversion
		Menu* possible_menu_item = dynamic_cast<Menu*>(search_deeper_iterator->second);

		if (possible_menu_item != nullptr)
		{
			possible_menu_item->search_for_command(command_name, found_paths);
		}

		++search_deeper_iterator;
	}
}


void Menu::run()
{
	std::cout << description << "\t" << command << "\n";

	AbstractMenuItem* chosen_item;

	do
	{
		print_options();
		chosen_item = choose_option();

		if (chosen_item == nullptr)
		{
			std::cout << no_item_found << "\n";
		}
		else
		{
			chosen_item->run();
		}
		
	} while (chosen_item != return_item);
}

void Menu::add_item(AbstractMenuItem* new_item)
{
	insert_item_into_map(item_map, new_item);
}

void Menu::delete_item(std::string item_command)
{
	AbstractMenuItem* deleted_item = item_map->find(item_command)->second;

	item_map->erase(item_map->find(item_command));

	delete deleted_item;
}

std::string Menu::to_string()
{
	std::string result;
	result += begin_menu; 
	result += begin_and_end_string;
	result += this->description;
	result += begin_and_end_string;
	result += description_command_separator;
	result += begin_and_end_string;
	result += this->command;
	result += begin_and_end_string;
	result += command_children_separator;

	std::map<std::string, AbstractMenuItem*>::iterator iterator = item_map->begin();
	for(; iterator != item_map->end(); ++iterator)
	{
		result += iterator->second->to_string();
		result += children_separator;
	}
	result += end_menu;

	return result;
}

void Menu::save_menu(std::string filename)
{
	std::ofstream destination(filename);

	if(destination.is_open())
	{
		destination << this->to_string();
	}

	destination.close();
}


Menu* Menu::open_menu(std::string filename)
{
	std::ifstream source(filename);
	std::string string_source;

	if(source.is_open())
	{
		std::stringstream stream;
		stream << source.rdbuf();
		string_source = stream.str();
	}
	source.close();

	return (new Parser(string_source))->parse();
}

void Menu::print_by_breadth()
{
	std::list<AbstractMenuItem*> queue;

	queue.emplace_back(this);
	queue.emplace_back(nullptr);

	print_by_breadth(&queue);
}

int Menu::get_number_of_children()
{
	return item_map->size();
}

//doesn't exactly work :/
void Menu::print_by_breadth(std::list<AbstractMenuItem*>* queue)
{
	AbstractMenuItem* top;

	while(!queue->empty())
	{
		top = queue->front();
		queue->pop_front();

		if(top != nullptr)
		{
			std::cout << top->get_command() << "\t";

			Menu* possible_menu = dynamic_cast<Menu*>(top);

			if (possible_menu != nullptr)
			{
				std::map<std::string, AbstractMenuItem*>::iterator it = possible_menu->item_map->begin();

				for (; it != possible_menu->item_map->end(); ++it)
				{
					queue->emplace_back(it->second);
				}
				queue->emplace_back(nullptr);
			}
		}
		else
		{
			std::cout << "\n";
		}
	}
}
