#pragma once
#include <boost/regex.hpp>
#include <fstream>
#include <string>
#include <unordered_map>
#include <memory>

#include "CRule.h"

class CGrammar
{
public:
	CGrammar(std::ifstream &input);

private:
	void InitRules(char state, std::string &rule);

	std::unordered_map<char, std::vector<CRule>> m_rules;

};