#include "CMooreMachine.h"

namespace
{
	const char CSV_SEPARATOR = ';';
	const size_t HEADER_ROWS = 2;
	const size_t MIN_STATES_COUNT = 1;
	const size_t MIN_TRANSFERS_COUNT = 1;

	auto throw_invalid_arg_if = [](bool predicate, const auto &message) {
		if (predicate) throw std::invalid_argument(message);
	};
}

CMooreMachine::CMooreMachine(std::ifstream &input)
{
	auto row_to_vect = [&]() -> std::vector<size_t> {
		std::vector<size_t> result;
		std::string str;
		getline(input, str);
		auto rowIds = CUtils::SplitString(str, CSV_SEPARATOR);
		for (auto idStr : rowIds) result.push_back(std::atoi(idStr.c_str()));
		if (result.size() > 0) result.erase(result.begin()); // FIX THIS!
		return result;
	};

	const Table &header = { row_to_vect(), row_to_vect() };
	InitStates(header);

	Table transfers;
	auto transferRow = row_to_vect();

	while (!transferRow.empty())
	{
		transfers.push_back(transferRow);
		transferRow = row_to_vect();
	}

	InitFullTable(header, transfers);
}

void CMooreMachine::InitStates(const Table &header)
{
	throw_invalid_arg_if(
		header.size() != HEADER_ROWS,
		"Invalid header size.");

	const auto &outs = header[0];
	const auto &states = header[1];

	throw_invalid_arg_if(
		outs.size() != states.size(),
		"States count not equal outputs count.");

	throw_invalid_arg_if(
		states.size() < MIN_STATES_COUNT,
		"States count less than " + std::to_string(MIN_STATES_COUNT) + ".");

	for (size_t i = 0; i < states.size(); ++i)
	{
		throw_invalid_arg_if(
			m_states.find(states[i]) != m_states.end(),
			"Duplicate states in header not allowed.");
		m_states.insert(std::make_pair(states[i], outs[i]));
	}
}

void CMooreMachine::InitFullTable(const Table &header, const Table &transfers)
{
	throw_invalid_arg_if(
		transfers.size() < MIN_TRANSFERS_COUNT,
		"Transfers less than " + std::to_string(MIN_TRANSFERS_COUNT));
	
	m_table.push_back(header[0]);
	m_table.push_back(header[1]);

	for (auto transfer : transfers)
	{
		throw_invalid_arg_if(
			transfer.size() < m_states.size(),
			"Transfers count less than states count.");
		m_table.push_back(std::vector<size_t>());

		for (size_t i = 0; i < transfer.size(); ++i)
		{
			throw_invalid_arg_if(
				m_states.find(transfer[i]) == m_states.end(),
				"Transfer state not found in states list.");
			m_table.back().push_back(transfer[i]);
		}
	}
}

bool CMooreMachine::Minimize()
{
	Table table = ZeroMinimize();
	Dictionary states = m_states;
	bool isMinimizeComplete = false;

	while (true)
	{
		Table tableCopy = table;
		Dictionary statesCopy = states;
		NextMinimize(table, states);
		if (table == tableCopy && states == statesCopy)
		{
			break;
		}
		isMinimizeComplete = true;
	}

	if (isMinimizeComplete)
	{
		Decompose(table, states);
		m_table = table;
		m_states = states;
	}

	return isMinimizeComplete;
}

Table CMooreMachine::ZeroMinimize()
{
	Table result = m_table;

	for (size_t i = 2; i < result.size(); ++i)
	{
		for (size_t j = 0; j < result[i].size(); ++j)
		{
			const auto &instanceTransfer = m_table[i][j];
			result[i][j] = m_states.find(instanceTransfer)->second;
		}
	}

	return result;
}

void CMooreMachine::Decompose(Table &table, Dictionary &states)
{
	std::unordered_map<size_t, size_t> uniqueClasses;

	for (size_t i = 0; i < table[1].size(); ++i)
	{
		const auto &newClass = states.find(table[1][i]);
		table[0][i] = newClass->second;
		uniqueClasses.insert(std::make_pair(newClass->second, newClass->first));
	}

	Table newTable = std::vector<std::vector<size_t>>(table.size());
	for (auto &row : newTable)
	{
		row.resize(uniqueClasses.size());
	}
	for (size_t i = 0; i < newTable[1].size(); i++)
	{
		const auto &newState = i + 1;
		newTable[1][i] = newState;
		newTable[0][i] = m_states.find(newState)->second;
	}

	for (size_t i = 2; i < newTable.size(); ++i)
	{
		for (auto &transfer : newTable[i])
		{

		}
	}
}

void CMooreMachine::NextMinimize(Table &table, Dictionary &states)
{
	auto to_hash = [&](size_t coll) -> std::string {
		const auto &state = table[1][coll];
		std::string result = std::to_string(states.find(state)->second);
		for (size_t row = 2; row < table.size(); ++row)
			result += std::to_string(table[row][coll]);
		return result;
	};

	std::unordered_map<std::string, size_t> stateIndexesByHash;
	std::vector<std::vector<size_t>> stateIndexes;

	auto add_hash_if = [&](const std::string hash, size_t newState) {
		if (stateIndexesByHash.find(hash) != stateIndexesByHash.end())
		{
			const auto &statesIndex = stateIndexesByHash.find(hash)->second;
			stateIndexes[statesIndex].push_back(newState);
			return;
		}
		stateIndexes.push_back(std::vector<size_t>());
		stateIndexes.back().push_back(newState);
		stateIndexesByHash.insert(std::make_pair(hash, stateIndexes.size() - 1));
	};

	for (size_t i = 0; i < m_table.front().size(); ++i)
	{
		add_hash_if(to_hash(i), table[1][i]);
	}

	for (size_t i = 0; i < stateIndexes.size(); ++i)
	{
		for (size_t j = 0; j < stateIndexes[i].size(); ++j)
		{
			states.find(stateIndexes[i][j])->second = i + 1;
		}
	}

	for (size_t i = 2; i < table.size(); ++i)
	{
		for (size_t j = 0; j < table[i].size(); ++j)
		{
			const auto &instanceTransfer = m_table[i][j];
			table[i][j] = states.find(instanceTransfer)->second;
		}
	}
}

std::string CMooreMachine::ToDotString()
{
	return std::string();
}

std::string CMooreMachine::ToString()
{
	std::string result;
	return result;
}

void CMooreMachine::Cleanup()
{
	m_states.clear();
	m_table.clear();
}