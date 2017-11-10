#include "CGrammar.h"
#include "Utils.h"

#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/remove_if.hpp>
#include <queue>
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

CGrammar::CGrammar(std::ifstream &input, GrammarType type)
{
	m_type = type;
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
	CreateStateIndexes();
}

void CGrammar::InitRules(char state, std::string &rule)
{
	std::vector<std::string> rules;
	boost::regex_split(std::back_inserter(rules), rule, RULE_SEPARATOR);

	for (auto &chain : rules)
	{
		chain.erase(boost::remove_if(chain, ::isspace), chain.end());
		const size_t &chainSize = chain.size();

		auto terminalCh = [&]() -> char {
			return chain[m_type == Left ? 0 : (chainSize == 1) ? 0 : 1];
		};
		auto stateCh = [&]()  {
			return chain[m_type == Left ? 1 : 0];
		};

		switch (chainSize)
		{
		case 1:
			invalid_arg_if(
				!CRule::IsTerminal(terminalCh()),
				"Invalid rule: " + to_rule_str(state, chain) + "\n");
			AddRule(state, CRule(terminalCh()));
			break;

		case 2:
			invalid_arg_if(
				!CRule::IsTerminal(terminalCh()) || !CRule::IsState(stateCh()),
				"Invalid rule: " + to_rule_str(state, chain) + "\n");
			AddRule(state, CRule(stateCh(), terminalCh()));
			break;

		default:
			invalid_arg_if(true, "Invalid rule: " + to_rule_str(state, chain) + "\n");
		}
	}
}

void CGrammar::AddRule(char state, const CRule &rule)
{
	m_rules[state].push_back(rule);
}

void CGrammar::ValidateRules() const
{
	invalid_arg_if(m_rules.find(START_STATE) == m_rules.end(), START_NOT_DECLARED);

	for (const auto &state : m_rules)
	{
		for (const auto &rule : state.second)
		{
			if (rule.IsTerminal())
			{
				return;
			}
			invalid_arg_if(
				m_rules.find(rule.GetState()) == m_rules.end(),
				(boost::format(STATE_NOT_DECLARED) % rule.GetState()).str());
		}
	}
}

void CGrammar::CreateRulesMap()
{
	std::stack<std::string> stateQueue;
	stateQueue.push(std::string(1, START_STATE));

	while (!stateQueue.empty())
	{
		const std::string state = stateQueue.top();
		stateQueue.pop();

		for (auto atomState : state)
		{
			for (auto &rule : m_rules.at(atomState))
			{
				const auto &destination = rule.IsTerminal() ? END_STATE : rule.GetState();
				auto &newState = m_table[state][rule.GetTerminal()];
				newState.insert(destination);
			}
		}

		for (auto newRow : m_table.at(state))
		{
			const auto &newState = to_state(newRow.second);

			if (m_table.find(newState) == m_table.end() && newState[0] != END_STATE)
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

	m_stateIndex[std::string({ END_STATE })] = maxIndex;
}

std::string CGrammar::ToGraph() const
{
	CDotWriter writer;

	for (const auto &row : m_table)
	{
		const auto &state = row.first;
		const auto type = state == std::string({ START_STATE }) ? Initial : Nonterminal;
		writer.PrintVertex(m_stateIndex.at(state), state, type);

		for (const auto &cell : row.second)
		{
			const auto &from = m_stateIndex.at(state);
			const auto &to = m_stateIndex.at(to_state(cell.second));
			writer.PrintEdge(from, to, { cell.first });
		}
	}

	const auto &endState = { END_STATE };
	writer.PrintVertex(m_stateIndex.at(endState), endState, Terminal);

	return writer.Get();
}
