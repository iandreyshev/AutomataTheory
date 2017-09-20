#include <string>
#include <iostream>

#include "CMealyTable.h"
#include "CDotWriter.h"
#include "CGraphPainter.h"

namespace
{
	const int ARGUMENTS_COUNT = 1;
	const std::string INSTANCE_DOT_NAME = "instance.dot";
	const std::string MINIMIZE_DOT_NAME = "mininmize.dot";
}

CMealyTable CreateTable(const std::string &tableFilename);
void CreateDotFiles(const CMealyTable &table);
void DrawMachine();

int main(int argc, char* argv[])
{
	try
	{
		if (argc < ARGUMENTS_COUNT)
		{
			throw new std::invalid_argument("Invalid arguments count.\nUse: MealyMachine.exe <table.xml>");
		}

		CMealyTable table = CreateTable(argv[0]);
		CreateDotFiles(table);
		CGraphPainter vizualizer(INSTANCE_DOT_NAME, MINIMIZE_DOT_NAME);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

CMealyTable CreateTable(const std::string &tableFilename)
{
	tinyxml2::XMLDocument xmlTable;

	try
	{
		xmlTable.LoadFile(tableFilename.c_str());
	}
	catch (const std::exception &e)
	{
		std::string msg = e.what();
		throw new std::invalid_argument("Can not load xml file:\n" + msg);
	}

	return CMealyTable(xmlTable);
}

void CreateDotFiles(const CMealyTable &table)
{
	(void)table;
}

void DrawMachine()
{

}