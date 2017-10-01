#include "CMooreMachine.h"
#include "CPrinter.h"
#include "Utils.h"
#include "CCommandHandler.h"

#include <iostream>
#include <functional>
#include <map>
#include <stdio.h>
#include <tchar.h>

void Intro();
void PrintHelp();
void DoCommand(int argc, char* argv[]);

namespace
{
	const int ARGUMENTS_COUNT = 2;
	const std::string INSTANCE_FILE = "instance";
	const std::string MINIMIZE_FILE = "minimize";
	const char* HELP_PATTERN = "%-24s%s";
	const std::string HELP_CMD = "-help";
	const std::map <std::string, std::function<void()>> CMD = {
		{ "-help", PrintHelp }
	};
}

int main(int argc, char* argv[])
{
	try
	{
		setlocale(LC_ALL, "rus");

		if (argc == 1)
		{
			Intro();
		}
		else
		{
			PrintHelp();
			//DoCommand(argc, argv);
		}
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void DoCommand(int argc, char* argv[])
{

}

void Intro()
{
	std::cout << std::endl;
}

void PrintHelp()
{
	printf("%s\n", "MachineDraw.exe commands:");
	printf(HELP_PATTERN, "-mmoore <machine>", "Минимизировать автомат мура");
	printf(HELP_PATTERN, "-mmealy <machine>", "Минимизировать автомат милли");
}