#include <string>
#include <locale>

#include "CMealyTable.h"
#include "CDotWriter.h"
#include "CGraphVizualizer.h"
#include "CUtils.h"

namespace
{
	const int ARGUMENTS_COUNT = 0;
	const std::string GRAPH = ".dot";
	const std::string IMAGE = ".png";
	const std::string INSTANCE_FILE = "instance";
	const std::string MINIMIZE_FILE = "minimize";
}

CMealyTable CreateTable(const std::string &tableFilename);
void CreateDotFiles(const CMealyTable &table);

int main(int argc, char* argv[])
{
	(void)argv;
	setlocale(LC_ALL, "rus");
	try
	{
		if (argc < ARGUMENTS_COUNT)
		{
			throw std::invalid_argument(
				"Недостаточно агрументов.\nИспользуйте: MealyMachine.exe <table.xml>");
		}

		CMealyTable table = CreateTable("");
		CreateDotFiles(table);

		CGraphVizualizer vizualizer(INSTANCE_FILE + IMAGE, MINIMIZE_FILE + IMAGE);
		vizualizer.Draw();
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
		throw std::invalid_argument("Failed to load xml-table:\n" + msg);
	}

	return CMealyTable(xmlTable);
}

void CreateDotFiles(const CMealyTable &table)
{
	CMealyTable minimizeTable = table.Minimize();
}