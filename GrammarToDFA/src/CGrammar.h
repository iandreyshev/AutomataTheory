#pragma once
#include "CRule.h"
#include <unordered_map>
#include <set>

using TableRow = std::unordered_map<char, std::set<char>>;
using Table = std::unordered_map<std::string, TableRow>;

class CGrammar
{
public:
	void Read(std::ifstream &input, bool isRight);

	std::string ToGraph() const;

private:
	bool ReadFromInput(std::ifstream &input, std::string &state, std::string &rules);
	void InitRule(char state, std::string &rule);
	void CreateRulesMap();
	void CreateStateIndexes();

	std::unordered_map<char, std::vector<CRule>> m_rules;
	std::unordered_map<std::string, size_t> m_stateIndex;
	Table m_table;
	bool m_isRight;
};