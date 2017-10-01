#include "CCommandHandler.h"

CCommandHandler::CCommandHandler(std::istream &input)
	: m_input(input)
{

}

void CCommandHandler::HandleCommand() const
{
	std::string command;

	while (std::cin >> command)
	{
		try
		{
			if (command == EXTI_COMMAND)
			{
				break;
			}
			if (m_commands.find(command) == m_commands.end())
			{
				Write("Invalid command. Use 'help' to view all commands.");
				continue;
			}
			m_commands.find(command)->second();
		}
		catch (std::exception e)
		{
			Write("Catch the exception: " + std::string(e.what()));
		}
	}

	Write("Goodbye!");
}

void CCommandHandler::Write(const std::string &message) const
{
	std::cout << CONSOLE_PREFIX << message << std::endl;
}

bool CCommandHandler::PrintHelp() const
{
	Write("Available commands:");
	printf("%-8s%-8d\n", "help", 1);
	return true;
}

bool CCommandHandler::MinimizeMoore() const
{
	return true;
}