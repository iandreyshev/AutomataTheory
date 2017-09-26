#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include "CUtils.h"
#include "libs/tinyxml2/tinyxml2.h"

using Table = std::vector<std::vector<size_t>>;
using IndexCollection = std::unordered_map<size_t, std::vector<size_t>>;

class CMooreMachine
{
public:
	CMooreMachine() = delete;
	CMooreMachine(std::ifstream &input);

	bool ToMinimize();
	std::string ToString();
	std::string ToDotString();
private:
	void InitHeader(const Table &tableHeader);
	void InitTransfers(const Table &transfersTable);

	void Cleanup();

	std::unordered_map<size_t, size_t> m_instStates;
	Table m_transfer;

};