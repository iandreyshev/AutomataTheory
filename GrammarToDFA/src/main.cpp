#include <iostream>
#include <fstream>
#include <string>
#include "CGrammar.h"
#include "Utils.h"

namespace
{
	const int ARGUMENTS_COUNT = 3;
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

		const std::string type = argv[1];
		const auto &file = argv[2];

		CGrammar grammar;
		std::ifstream input(file);
		grammar.Read(input, type == "right");
		Utils::ToImage(grammar.ToGraph(), argv[1]);
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}