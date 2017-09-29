#pragma once
#include <string>
#include <unordered_map>
#include <set>
#include <map>
#include <fstream>
#include <algorithm>
#include "CUtils.h"
#include "libs/tinyxml2/tinyxml2.h"

using IdList = std::vector<size_t>;
using Table = std::vector<IdList>;
using Dictionary = std::unordered_map<size_t, size_t>;
using DictionaryList = std::unordered_map<size_t, IdList>;

class CMooreMachine
{
public:
	CMooreMachine() = delete;
	CMooreMachine(std::ifstream &input);

	bool Minimize();
	std::string ToString();
	std::string ToDotString();
private:
	void InitStates(const Table &header);
	void InitFullTable(const Table &tableHeader, const Table &transfersTable);
	void InitTransfersMap();

	Table ZeroMinimize();
	void NextMinimize(Table &table, Dictionary &states);
	void CreateNewTable(Table &table, Dictionary &states);

	void Cleanup();

	Dictionary m_classesByStates;
	DictionaryList m_transfersByState;
	Table m_table;
};