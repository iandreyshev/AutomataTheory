#include <iostream>
#include <fstream>
#include <string>
#include "CGrammar.h"
#include "Utils.h"

namespace
{
	const int ARGUMENTS_COUNT = 2;
}

int main(int argc, char* argv[])
{
	try
	{
		if (argc < ARGUMENTS_COUNT)
		{
			std::cout << "Invalid arguments count."
				<< "Use: program.exe <input file>" << std::endl;
			return EXIT_FAILURE;
		}

		std::ifstream input(argv[1]);
		CGrammar grammar(input);
		Utils::ToImage(grammar.ToGraph(), "result");
	}
	catch (const std::exception ex)
	{
		std::cout << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}