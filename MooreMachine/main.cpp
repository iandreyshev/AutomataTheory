#include "CMooreMachine.h"
#include "CDotWriter.h"

#include <string>
#include <fstream>
#include <iostream>

namespace
{
	const int ARGUMENTS_COUNT = 1;
}

int main(int argc, char* argv[])
{
	try
	{
		if (argc < ARGUMENTS_COUNT)
		{
			throw std::invalid_argument(
				"Invalid arguments count.\nUse: MooreMachine.exe <input>");
		}

		std::ifstream input(argv[1]);
		CMooreMachine machine(input);
		//machine.ToMinimize();
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}