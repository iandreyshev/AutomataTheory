#include "CGrammar.h"
#include "Util.h"
#include <exception>
#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/remove_if.hpp>

namespace
{
	const boost::regex STATE_SEPARATOR = boost::regex("[>]");
	const boost::regex RULE_SEPARATOR = boost::regex("[|]");
	const size_t MIN_CHAIN_SIZE = 1;
	const size_t MAX_CHAIN_SIZE = 2;

	auto invalid_arg_if = [](bool predicate, const std::string &message) {
		if (predicate) {
			throw std::invalid_argument(message);
		}
	};
	auto to_rule = [](char state, const std::string &chain) {
		return state + " > " + chain;
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
		Util::TrimString(state);
		std::string rule = symbols[1];

		InitRules(state[0], rule);
	}
}

void CGrammar::InitRules(char state, std::string &rule)
{
	std::vector<std::string> rules;
	boost::regex_split(std::back_inserter(rules), rule, RULE_SEPARATOR);

	for(auto &chain : rules)
	{
		chain.erase(boost::remove_if(chain, ::isspace), chain.end());

		switch (chain.size())
		{
		case 1:
			invalid_arg_if(
				!CRule::IsTerminal(chain[0]),
				"Invalid rule: " + to_rule(state, chain));
			m_rules[state].push_back(CRule(chain[0]));
			break;
		case 2:
			invalid_arg_if(
				!CRule::IsTerminal(chain[0]) || !CRule::IsState(chain[1]),
				"Invalid rule: " + to_rule(state, chain));
			m_rules[state].push_back(CRule(chain[0], chain[1]));
			break;
		default:
			throw std::invalid_argument("Invalid rule: " + to_rule(state, chain));
		}
	}
}
