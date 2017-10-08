#include "CMooreMachine.h"

namespace
{
	auto throw_invalid_arg_if = [](bool predicate, const auto &message) {
		if (predicate) throw std::invalid_argument(message);
	};
}

CMooreMachine::CMooreMachine(std::ifstream &input)
{
	auto outs = Machine::read_moore_line<size_t>(input);
	auto states = Machine::read_moore_line<size_t>(input);

	InitStates(outs, states);

	Table transfers;
	auto transferRow = Machine::read_moore_line<size_t>(input);

	while (!transferRow.empty())
	{
		transferRow.erase(transferRow.begin());
		transfers.push_back(transferRow);
		transferRow = Machine::read_moore_line<size_t>(input);
	}

	InitFullTable(outs, states, transfers);
	InitTransfersMap();
}

void CMooreMachine::InitStates(const IdList &outs, const IdList &states)
{
	throw_invalid_arg_if(
		outs.size() != states.size(),
		"States count not equal outputs count.");

	throw_invalid_arg_if(
		states.size() < Machine::MIN_STATES_COUNT,
		"States count less than " + std::to_string(Machine::MIN_STATES_COUNT) + ".");

	for (size_t i = 0; i < states.size(); ++i)
	{
		throw_invalid_arg_if(
			m_classesByState.find(states[i]) != m_classesByState.end(),
			"Duplicate states in header not allowed.");
		m_classesByState.insert(std::make_pair(states[i], outs[i]));
	}
}

void CMooreMachine::InitFullTable(const IdList &outs, const IdList &states, const Table &transfers)
{
	throw_invalid_arg_if(
		transfers.size() < Machine::MIN_TRANSFERS_COUNT,
		"Transfers less than " + std::to_string(Machine::MIN_TRANSFERS_COUNT));
	
	m_table.push_back(outs);
	m_table.push_back(states);

	for (auto transfer : transfers)
	{
		throw_invalid_arg_if(
			transfer.size() < m_classesByState.size(),
			"Transfers count less than states count.");
		m_table.push_back(IdList());

		for (size_t i = 0; i < transfer.size(); ++i)
		{
			throw_invalid_arg_if(
				m_classesByState.find(transfer[i]) == m_classesByState.end(),
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
		const auto state = m_table[1][i];

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
	Dictionary states = m_classesByState;
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
			const auto instanceTransfer = m_table[i][j];
			result[i][j] = m_classesByState.find(instanceTransfer)->second;
		}
	}

	return result;
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
		newTable[0][tableColl] = m_classesByState.find(tableClass.second)->second;
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
	m_classesByState = classByStates;
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
		const auto label =
			Machine::STATE_NAME + std::to_string(state) + " / " +
			Machine::OUT_NAME + std::to_string(out);
		writer.PrintVertex(state, label, StateType::Initial);

		for (size_t j = 2; j < m_table.size(); ++j)
		{
			const auto edgeLabel = Machine::INPUT_NAME + std::to_string(j - 1);
			writer.PrintEdge(state, m_table[j][i], edgeLabel);
		}
	}

	writer.~CDotWriter();

	return stream.str();
}

void CMooreMachine::OnCleanup()
{
	m_transfersByState.clear();
	m_classesByState.clear();
}