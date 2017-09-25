#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include "CUtils.h"
#include "libs/tinyxml2/tinyxml2.h"

struct MooreTable
{
	std::unordered_map<size_t, size_t> states;
	std::unordered_map<size_t, std::vector<size_t>> input;
};

class CMooreMachine
{
public:
	CMooreMachine() = delete;
	CMooreMachine(std::ifstream &input);
	//CMooreMachine(const tinyxml2::XMLDocument &table);

	bool Minimize();
	std::string ToString();
	std::string ToDotString();
private://equivalence
	MooreTable m_table;

	static bool ToZeroEquClass(MooreTable &table);
	static bool ToNextEquClass(MooreTable &table);

};