#pragma once
#include "AbstractAction.h"
#include <map>
#include "AbstractMenuItem.h"
#include "Menu.h"

class DefaultAction : public AbstractAction
{
public:
	//default constructor and destructor
	void perform_action() const override;
};

//------------------------------------------------------------------------------

static const std::string help_item_command = "help";
static const std::string help_item_description = "Get help for a command in the menu.";
static const std::string help_item_help = "Prints additional information about a given command.";

/**
 * Action for searching for help in a menu.
 */
class HelpAction :
	public AbstractAction
{
public:
	HelpAction(std::map<std::string, AbstractMenuItem*>* item_map);
	//default destructor
	void perform_action() const override;
private:
	std::map<std::string, AbstractMenuItem*>* item_map;
};

//---------------------------------------------------------------------------

static const std::string return_item_command = "return";
static const std::string return_item_description = "Return to previous menu";
static const std::string return_item_help = "Returns to previous menu";

class ReturnAction :
	public AbstractAction
{
public:
	//default destructor and constructor
	void perform_action() const override;
};

//----------------------------------------------------------------------------

static const std::string search_item_command = "search";
static const std::string search_item_description = "Search in whole menu.";
static const std::string search_item_help = "Returns all paths to items with given command.";

/**
 * Action for searching the menu for items with a given command
 */
class SearchAction : public AbstractAction
{
public:
	SearchAction(Menu* root_menu);
	//default destructor
	void perform_action() const override;

private:
	Menu* root_menu;
};