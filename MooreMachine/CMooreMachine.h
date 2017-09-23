#pragma once
#include <string>
#include <set>
#include <map>
#include "libs/tinyxml2/tinyxml2.h"

struct MooreNode
{
	size_t index;
	std::string output;
};

class CMooreMachine
{
public:
	CMooreMachine() = delete;
	CMooreMachine(const tinyxml2::XMLDocument &table);

	bool Minimize();
	std::string ToDotString();
private:
	std::set<size_t> m_startStates;
	std::set<size_t> m_endStates;
	std::map<std::string, size_t> m_statesIndexes;
	std::map<size_t, std::string> m_statesOuts;

};