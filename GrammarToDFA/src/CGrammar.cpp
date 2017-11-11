#include "CGrammar.h"
#include "Utils.h"

#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/remove_if.hpp>
#include <stack>

namespace
{
	const boost::regex STATE_SEPARATOR = boost::regex("[>]");
	const boost::regex RULE_SEPARATOR = boost::regex("[|]");

	const std::string STATE_NOT_DECLARED = "The state '%1%' is not declared";
	const std::string START_NOT_DECLARED = "The start state 'S' must be declared";

	const size_t MIN_CHAIN_SIZE = 1;
	const size_t MAX_CHAIN_SIZE = 2;

	const char START_STATE = 'S';
	const char END_STATE = '#';

	auto invalid_arg_if = [](bool predicate, const std::string &message) {
		if (!predicate) return;
		throw std::invalid_argument(message);
	};
	auto to_rule_str = [](char state, const std::string &chain) {
		return "'" + std::string(1, state) + " > " + chain + "'";
	};
	auto to_state = [](const std::set<char> &state) {
		std::string result = "";
		for (const auto &ch : state) result += { ch };
		return result;
	};
}

void CGrammar::Read(std::ifstream &input, bool isRight)
{
	m_rules.clear();
	m_table.clear();
	m_stateIndex.clear();
	m_isRight = isRight;
	std::string state;
	std::string rules;

	while (ReadFromInput(input, state, rules))
	{
		InitRule(state[0], rules);
	}

	CreateRulesMap();
	CreateStateIndexes();
}

bool CGrammar::ReadFromInput(std::ifstream &input, std::string &state, std::string &rules)
{
	std::string line;

	if (!getline(input, line))
	{
		return false;
	}

	std::vector<std::string> symbols;
	boost::regex_split(std::back_inserter(symbols), line, STATE_SEPARATOR);
	invalid_arg_if(symbols.size() < 2, "Invalid rule format");

	state = symbols[0];
	Utils::TrimString(state);
	rules = symbols[1];

	return true;
}

void CGrammar::InitRule(char state, std::string &ruleStr)
{
	std::vector<std::string> rules;
	boost::regex_split(std::back_inserter(rules), ruleStr, RULE_SEPARATOR);

	for (auto &chain : rules)
	{
		chain.erase(boost::remove_if(chain, ::isspace), chain.end());

		switch (chain.size())
		{
		case 1:
		{
			CRule rule = m_isRight ? CRule(state, chain[0]) : CRule(chain[0]);
			char start = m_isRight ? END_STATE : state;
			m_rules[start].push_back(rule);
			break;
		}
		case 2:
		{
			CRule rule = m_isRight ? CRule(state, chain[1]) : CRule(chain[1], chain[0]);
			char start = m_isRight ? chain[0] : state;
			m_rules[start].push_back(rule);
			break;
		}
		}
	}
}

void CGrammar::CreateRulesMap()
{
	const auto &start = std::string(1, m_isRight ? END_STATE : START_STATE);
	const auto &end = m_isRight ? START_STATE : END_STATE;

	std::stack<std::string> stateQueue;
	stateQueue.push(start);
	m_table[start];

	while (!stateQueue.empty())
	{
		const std::string state = stateQueue.top();
		stateQueue.pop();

		for (auto atomState : state)
		{
			for (auto &rule : m_rules.at(atomState))
			{
				const auto &destination = rule.IsTerminal() ? end : rule.GetState();
				auto &newState = m_table[state][rule.GetTerminal()];
				newState.insert(destination);
			}
		}

		for (auto newRow : m_table.at(state))
		{
			const auto &newState = to_state(newRow.second);

			if (m_table.find(newState) == m_table.end() && newState[0] != end)
			{
				stateQueue.push(newState);
			}
		}
	}
}

void CGrammar::CreateStateIndexes()
{
	size_t maxIndex = 0;

	for (const auto &state : m_table)
	{
		m_stateIndex[state.first] = maxIndex;
		++maxIndex;
	}

	const auto &endState = std::string(1, m_isRight ? START_STATE : END_STATE);
	m_stateIndex[endState] = maxIndex;
}

std::string CGrammar::ToGraph() const
{
	const auto &start = std::string(1, m_isRight ? END_STATE : START_STATE);
	const auto &end = std::string(1, m_isRight ? START_STATE : END_STATE);
	CDotWriter writer;

	for (const auto &row : m_table)
	{
		const auto &state = row.first;
		const auto type = state == start ? Initial : Nonterminal;
		writer.PrintVertex(m_stateIndex.at(state), state, type);

		for (const auto &cell : row.second)
		{
			const auto &from = m_stateIndex.at(state);
			const auto &to = m_stateIndex.at(to_state(cell.second));
			writer.PrintEdge(from, to, { cell.first });
		}
	}

	writer.PrintVertex(m_stateIndex.at(end), end, Terminal);

	return writer.Get();
}
