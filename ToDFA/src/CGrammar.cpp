#include "CGrammar.h"
#include "Utils.h"

#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/remove_if.hpp>

namespace
{
	const boost::regex STATE_SEPARATOR = boost::regex("[>]");
	const boost::regex RULE_SEPARATOR = boost::regex("[|]");

	const std::string STATE_NOT_DECLARED = "The state '%1%' is not declared";

	const size_t MIN_CHAIN_SIZE = 1;
	const size_t MAX_CHAIN_SIZE = 2;

	const char START_STATE = 'S';
	const char END_STATE = ' ';

	auto invalid_arg_if = [](bool predicate, const std::string &message) {
		if (!predicate) return;
		throw std::invalid_argument(message);
	};
	auto to_rule_string = [](char state, const std::string &chain) {
		return "'" + std::string({state}) + " > " + chain + "'";
	};
}

CGrammar::CGrammar(std::ifstream &input)
{
	std::string line;

	while (getline(input, line))
	{
		std::vector<std::string> symbols;
		boost::regex_split(std::back_inserter(symbols), line, STATE_SEPARATOR);
		invalid_arg_if(symbols.size() < 2, "Invalid rule format");

		std::string state = symbols[0];
		Utils::TrimString(state);
		std::string rule = symbols[1];

		InitRules(state[0], rule);
	}

	ValidateRules();
	CreateRulesMap();
}

void CGrammar::InitRules(char state, std::string &rule)
{
	std::vector<std::string> rules;
	boost::regex_split(std::back_inserter(rules), rule, RULE_SEPARATOR);

	for (auto &chain : rules)
	{
		chain.erase(boost::remove_if(chain, ::isspace), chain.end());

		switch (chain.size())
		{
		case 1:
			invalid_arg_if(
				!CRule::IsTerminal(chain[0]),
				"Invalid rule: " + to_rule_string(state, chain) + "\n"
			);
			AddRule(state, CRule(chain[0]));
			break;

		case 2:
			invalid_arg_if(
				!CRule::IsTerminal(chain[0]) || !CRule::IsState(chain[1]),
				"Invalid rule: " + to_rule_string(state, chain) + "\n"
			);
			AddRule(state, CRule(chain[0], chain[1]));
			break;

		default:
			invalid_arg_if(true, "Invalid rule: " + to_rule_string(state, chain) + "\n");
		}
	}
}

void CGrammar::AddRule(char state, const CRule &rule)
{
	char terminal = rule.GetTerminal();

	if (m_terminals.find(terminal) == m_terminals.end() &&
		!CRule::IsEnd(terminal))
	{
		++m_maxTerminalIndex;
		m_terminals.insert(std::make_pair(terminal, m_maxTerminalIndex));
	}

	m_rules[state].push_back(rule);
}

void CGrammar::ValidateRules() const
{
	for (const auto &state : m_rules)
	{
		for (const auto &rule : state.second)
		{
			if (rule.IsTerminal())
			{
				return;
			}
			char inRuleState = rule.GetState();
			invalid_arg_if(
				m_rules.find(inRuleState) == m_rules.end(),
				(boost::format(STATE_NOT_DECLARED) % inRuleState).str()
			);
		}
	}
}

void CGrammar::CreateRulesMap()
{

}

std::string CGrammar::ToGraph() const
{
	return "";
}