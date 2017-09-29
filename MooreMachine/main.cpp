#include "CMooreMachine.h"
#include "CDotWriter.h"
#include "CPrinter.h"

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>

namespace
{
	const int ARGUMENTS_COUNT = 2;
	const std::string GRAPH_TYPE = ".dot";
	const std::string IMG_TYPE = ".png";
	const std::string INSTANCE_FILE = "instance";
	const std::string MINIMIZE_FILE = "minimize";
	const std::string CONVERT_COMMAND = "dot -Tpng -o";
}

void ConvertToImage(const CMooreMachine &machine, const std::string &fileName);

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
		CMooreMachine instance(input);
		CMooreMachine instanceCopy = instance;
		instance.Minimize();

		ConvertToImage(instanceCopy, INSTANCE_FILE);
		ConvertToImage(instance, MINIMIZE_FILE);

		CPrinter::Draw(INSTANCE_FILE + IMG_TYPE, MINIMIZE_FILE + IMG_TYPE);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void ConvertToImage(const CMooreMachine &machine, const std::string &fileName)
{
	const std::string &dotName = fileName + GRAPH_TYPE;
	const std::string &imageName = fileName + IMG_TYPE;

	std::ofstream dotFile(dotName);
	dotFile << machine.ToDotString();
	dotFile.close();

	CUtils::RunProcess(CONVERT_COMMAND + imageName + " " + dotName);
}