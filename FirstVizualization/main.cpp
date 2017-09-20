#include "CUtils.h"
#include "CDotWriter.h"
#include <fstream>

namespace
{
	const std::string DOT_COMMAND = "dot -Tpng -oresult.png graph.dot";
}

int main()
{
	std::string graphFileName = "graph.dot";
	std::ofstream graphFile(graphFileName);
	CDotWriter dotWriter(graphFile);

	dotWriter.PrintVertex(0, "A", Terminal);
	dotWriter.PrintVertex(1, "B", Initial);
	dotWriter.PrintEdge(0, 1, "x");
	dotWriter.~CDotWriter();
	graphFile.close();

	if (!CUtils::RunProcess("dot -Tpng -o result.png graph.dot"))
	{
		return 1;
	}

	return 0;
}