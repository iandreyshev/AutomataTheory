#pragma once
#include <string>
#include <unordered_map>
#include <set>
#include <fstream>
#include <algorithm>
#include "CUtils.h"
#include "libs/tinyxml2/tinyxml2.h"

using Table = std::vector<std::vector<size_t>>;
using Dictionary = std::unordered_map<size_t, size_t>;

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

	Table ZeroMinimize();
	void NextMinimize(Table &table, Dictionary &states);
	void Decompose(Table &table, Dictionary &states);

	void Cleanup();

	Dictionary m_states;
	Table m_table;
};