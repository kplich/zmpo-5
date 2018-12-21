#pragma once

/**
 * Generic interface for defining actions for commands.
 */
class AbstractAction
{
public:
	/**
	 * Default constructor, for subclasses to invoke.
	 */
	AbstractAction();

	/**
	 * Virtual destructor.
	 */
	virtual ~AbstractAction();

	/**
	 * Method running the contents of the command.
	 */
	virtual void perform_action() const = 0;
};

