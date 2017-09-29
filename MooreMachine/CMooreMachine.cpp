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
	auto row_to_list = [&](bool isEraseFirst = true) -> IdList {
		IdList result;
		std::string str;
		getline(input, str);
		auto strItems = CUtils::SplitString(str, CSV_SEPARATOR);
		for (auto item : strItems) result.push_back(std::atoi(item.c_str()));
		if (isEraseFirst = true && !result.empty()) result.erase(result.begin());
		return result;
	};

	const Table &header = { row_to_list(), row_to_list() };
	InitStates(header);

	Table transfers;
	auto transferRow = row_to_list();

	while (!transferRow.empty())
	{
		transfers.push_back(transferRow);
		transferRow = row_to_list();
	}

	InitFullTable(header, transfers);
	InitTransfersMap();
}

void CMooreMachine::InitStates(const Table &header)
{
	throw_invalid_arg_if(
		header.size() != HEADER_ROWS,
		"Invalid header size.");

	const auto &classes = header[0];
	const auto &states = header[1];

	throw_invalid_arg_if(
		classes.size() != states.size(),
		"States count not equal outputs count.");

	throw_invalid_arg_if(
		states.size() < MIN_STATES_COUNT,
		"States count less than " + std::to_string(MIN_STATES_COUNT) + ".");

	for (size_t i = 0; i < states.size(); ++i)
	{
		throw_invalid_arg_if(
			m_classesByStates.find(states[i]) != m_classesByStates.end(),
			"Duplicate states in header not allowed.");
		m_classesByStates.insert(std::make_pair(states[i], classes[i]));
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
			transfer.size() < m_classesByStates.size(),
			"Transfers count less than states count.");
		m_table.push_back(IdList());

		for (size_t i = 0; i < transfer.size(); ++i)
		{
			throw_invalid_arg_if(
				m_classesByStates.find(transfer[i]) == m_classesByStates.end(),
				"Transfer state not found in states list.");
			m_table.back().push_back(transfer[i]);
		}
	}
}

void CMooreMachine::InitTransfersMap()
{
	m_transfersByState.clear();

	for (size_t i = 0; i < m_table[1].size(); ++i)
	{
		const auto &state = m_table[1][i];

		for (size_t j = 2; j < m_table.size(); ++j)
		{
			auto &list = m_transfersByState[state];
			list.push_back(m_table[j][i]);
		}
	}
}

bool CMooreMachine::Minimize()
{
	Table table = ZeroMinimize();
	Dictionary states = m_classesByStates;
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
		CreateNewTable(table, states);
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
			result[i][j] = m_classesByStates.find(instanceTransfer)->second;
		}
	}

	return result;
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

void CMooreMachine::CreateNewTable(Table &table, Dictionary &classByStates)
{
	std::map<size_t, size_t> stateByClasses;

	for (size_t i = 0; i < table[1].size(); ++i)
	{
		const auto &newClass = classByStates.find(table[1][i]);
		stateByClasses.insert(std::make_pair(newClass->second, newClass->first));
	}

	Table newTable = Table(table.size(), IdList(stateByClasses.size()));
	size_t tableColl = 0;

	for (const auto &tableClass : stateByClasses)
	{
		newTable[0][tableColl] = m_classesByStates.find(tableClass.second)->second;
		newTable[1][tableColl] = tableClass.first;
		++tableColl;
	}

	for (size_t i = 0; i < newTable[1].size(); ++i)
	{
		const auto &state = stateByClasses.at(newTable[1][i]);

		for (size_t j = 2; j < newTable.size(); ++j)
		{
			const auto &transferState = m_transfersByState.at(state)[j - 2];
			newTable[j][i] = classByStates.at(transferState);
		}
	}

	m_table = newTable;
	m_classesByStates = classByStates;
	InitTransfersMap();
}

std::string CMooreMachine::ToDotString() const
{
	std::stringstream stream;
	CDotWriter writer(stream);

	for (size_t i = 0; i < m_table.front().size(); ++i)
	{
		const auto out = m_table[0][i];
		const auto state = m_table[1][i];
		const auto label = "s" + std::to_string(state) + " / y" + std::to_string(out);
		writer.PrintVertex(state, label, StateType::Nonterminal);

		for (size_t j = 2; j < m_table.size(); ++j)
		{
			const auto edgeLabel = "x" + std::to_string(j - 1);
			writer.PrintEdge(state, m_table[j][i], edgeLabel);
		}
	}

	writer.~CDotWriter();

	return stream.str();
}

std::string CMooreMachine::ToString() const
{
	std::string result;
	return result;
}

void CMooreMachine::Cleanup()
{
	m_transfersByState.clear();
	m_classesByStates.clear();
	m_table.clear();
}