#pragma once
#include <functional>
#include <vector>
#include <sstream>
#include "tinyxml2/tinyxml2.h"
#include "CDotWriter.h"
#include "CUtils.h"
#include <map>
#include <set>
#include <algorithm>

struct MealyEdge
{
	size_t destIndex;
	std::string output;
};

using MealyInput = std::map<std::string, MealyEdge>;
using MealyTable = std::map<size_t, MealyInput>;

class CMealyMachine
{
public:
	CMealyMachine(const tinyxml2::XMLDocument &xmlTable);
	CMealyMachine ToMinimize() const;
	std::string ToDotString() const;

private:
	std::set<size_t> m_start;
	std::set<size_t> m_end;
	MealyTable m_table;
	std::map<std::string, size_t> m_states;

	CMealyMachine(const MealyTable &table);
	void InitTerminals(const tinyxml2::XMLElement* root);
	void InitTable(const XMLElementCollection &statesNodes);
	void InitStates(const XMLElementCollection &statesNodes);

	size_t GetStateIndex(const std::string &name) const;
	StateType GetStateType(size_t index) const;

	void Cleanup();

};