#pragma once
#include "CRule.h"
#include <unordered_map>
#include <set>

using TableRow = std::unordered_map<char, std::set<char>>;
using Table = std::unordered_map<std::string, TableRow>;

enum GrammarType
{
	Left,
	Right,
};

class CGrammar
{
public:
	CGrammar(std::ifstream &input, GrammarType type);
	std::string ToGraph() const;

private:
	void InitRules(char state, std::string &rule);
	void AddRule(char state, const CRule &rule);
	void ValidateRules() const;
	void CreateRulesMap();
	void CreateStateIndexes();

	GrammarType m_type;
	std::unordered_map<char, std::vector<CRule>> m_rules;
	std::unordered_map<std::string, size_t> m_stateIndex;
	Table m_table;

};