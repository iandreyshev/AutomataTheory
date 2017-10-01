#include "stdafx.h"

void Intro();
void MinimizeMoore(int argc, char* argv[]);
void MinimizeMealy(int argc, char* argv[]);
void PrintHelp(int argc, char* argv[]);
void ErrCommand(char* command);

namespace
{
	const int MIN_ARGS_COUNT = 2;
	const int MINIMIZE_ARGS_COUNT = 3;

	const std::map<std::string, std::function<void(int, char*[])>> COMMANDS = {
		{ "-help", PrintHelp },
		{ "-mmoore", MinimizeMoore },
		{ "-mmealy", MinimizeMealy }
	};
}

int main(int argc, char* argv[])
{
	try
	{
		setlocale(LC_ALL, "");

		if (argc < MIN_ARGS_COUNT)
		{
			Intro();
		}
		else if (COMMANDS.find(argv[1]) != COMMANDS.end())
		{
			COMMANDS.at(argv[1])(argc, argv);
		}
		else
		{
			ErrCommand(argv[1]);
		}
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void Intro()
{
	printf("%s\n", "Automata.exe v1.0");
	printf("%s\n", "Use '-help' to see all available commands.");
}

void MinimizeMoore(int argc, char* argv[])
{
	if (argc < MINIMIZE_ARGS_COUNT)
	{
		throw std::invalid_argument("Minimization: Invalid arguments count.\n");
	}

	std::ifstream input(argv[2]);
	CMooreMachine machine(input);
	CMooreMachine minimizedMachine = machine;
	minimizedMachine.Minimize();

	auto normalImage = Utils::ToImage(machine, "normal_machine");
	auto minimizedImage = Utils::ToImage(machine, "minimized_machine");
	CPrinter::Draw(normalImage, minimizedImage);
}

void MinimizeMealy(int argc, char* argv[])
{
	if (argc < MINIMIZE_ARGS_COUNT)
	{
		throw std::invalid_argument("Minimization: Invalid arguments count.\n");
	}

	(void)argv;
}

void PrintHelp(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	printf("%s\n", "Automata commands:");
	printf("%-24s%s\n", "-mmoore <machine>", "Минимизировать автомат мура");
	printf("%-24s%s\n", "-mmealy <machine>", "Минимизировать автомат милли");
}

void ErrCommand(char* command)
{
	printf("%s '%s'\n", "Automata: Invalid command", command);
	printf("%s\n", "Use '-help' to see all available commands");
}
