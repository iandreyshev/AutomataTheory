#pragma once
#include "CRule.h"
#include <unordered_map>

using TableRow = std::unordered_map<char, std::string>;
using Table = std::unordered_map<std::string, TableRow>;

enum GrammarType
{
	Left,
	Right,
};

class CGrammar
{
public:
	CGrammar(std::ifstream &input);
	std::string ToGraph() const;

private:
	void InitRules(char state, std::string &rule);
	void AddRule(char state, const CRule &rule);
	void ValidateRules() const;
	void CreateRulesMap();
	void CreateStateIndexes();

	std::unordered_map<char, std::vector<CRule>> m_rules;
	std::unordered_map<std::string, size_t> m_stateIndex;
	Table m_table;

};