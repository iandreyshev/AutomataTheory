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

struct MealyNode
{
	size_t index;
	size_t destIndex;
	std::string out;
};

using MealyNodesVec = std::vector<MealyNode>;
using MealyTable = std::map<std::string, MealyNodesVec>;

class CMealyMachine
{
public:
	CMealyMachine(const tinyxml2::XMLDocument &xmlTable);
	CMealyMachine ToMinimize() const;
	std::string ToDotString() const;

private:
	MealyTable m_table;
	std::map<std::string, size_t> m_statesMap;

	CMealyMachine(const MealyTable &table);
	void InitInputAlphabet(const XMLElementCollection &inCollection);
	void InitStatesCollection(const XMLElementCollection &inCollection);
	void InitTable(const XMLElementCollection &inCollection);
	void Cleanup();

};