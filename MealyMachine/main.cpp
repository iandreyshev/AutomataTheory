#include <string>
#include <locale>

#include "CMealyMachine.h"
#include "CDotWriter.h"
#include "CGraphVizualizer.h"
#include "CUtils.h"

namespace
{
	const char* XML_TABLE = "table.xml";
	const std::string GRAPH = ".dot";
	const std::string IMAGE = ".png";
	const std::string INSTANCE_FILE = "instance";
	const std::string MINIMIZE_FILE = "minimize";
}

void CreateDotFiles(const CMealyMachine &table);

int main()
{
	try
	{
		tinyxml2::XMLDocument xmlTable(true);
		xmlTable.SetBOM(true);
		xmlTable.LoadFile(XML_TABLE);
		CMealyMachine mealyMachine(xmlTable);
		CreateDotFiles(mealyMachine);

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

void CreateDotFiles(const CMealyMachine &table)
{
	CMealyMachine minimizeTable = table.ToMinimize();
}