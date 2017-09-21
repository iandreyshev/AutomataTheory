#include "CMealyTable.h"
#include "CUtils.h"

CMealyTable::CMealyTable(const tinyxml2::XMLDocument &xmlTable)
{
	(void)xmlTable;
}

CMealyTable::CMealyTable()
{
}

CMealyTable CMealyTable::Minimize() const
{
	return CMealyTable();
}