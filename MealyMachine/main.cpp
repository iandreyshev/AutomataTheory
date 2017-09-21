#include <string>
#include <locale>
#include <fstream>

#include "CMealyMachine.h"
#include "CDotWriter.h"
#include "CGraphVizualizer.h"
#include "CUtils.h"

namespace
{
	const char* XML_TABLE = "table.xml";

	const std::string GRAPH_TYPE = ".dot";
	const std::string IMG_TYPE = ".png";
	const std::string INSTANCE_FILE = "instance";
	const std::string MINIMIZE_FILE = "minimize";
	const std::string CONVERT_COMMAND = "dot -Tpng -o";
}

void ConvertToImage(const CMealyMachine &machine, const std::string &fileName);

int main()
{
	try
	{
		tinyxml2::XMLDocument xmlTable(true);
		xmlTable.LoadFile(XML_TABLE);
		CMealyMachine mealyMachine(xmlTable);

		ConvertToImage(mealyMachine, INSTANCE_FILE);
		ConvertToImage(mealyMachine, MINIMIZE_FILE);

		CGraphVizualizer painter(INSTANCE_FILE + IMG_TYPE, MINIMIZE_FILE + IMG_TYPE);
		painter.Draw();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void ConvertToImage(const CMealyMachine &machine, const std::string &fileName)
{
	const std::string &dotName = fileName + GRAPH_TYPE;
	const std::string &imageName = fileName + IMG_TYPE;

	std::ofstream dotFile(dotName);
	dotFile << machine.ToDotString();
	dotFile.close();

	CUtils::RunProcess(CONVERT_COMMAND + imageName + " " + dotName);
}