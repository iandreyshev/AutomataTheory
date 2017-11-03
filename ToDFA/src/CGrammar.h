#pragma once
#include "CRule.h"
#include <unordered_map>

class CGrammar
{
public:
	CGrammar(std::ifstream &input);

	void AddRule(char state, const CRule &rule);
	std::string ToGraph() const;

private:
	void InitRules(char state, std::string &rule);
	void ValidateRules() const;
	void CreateRulesMap();

	std::unordered_map<char, std::vector<CRule>> m_rules;
	std::unordered_map<char, size_t> m_terminals;

	size_t m_maxTerminalIndex = 0;

};