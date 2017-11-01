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

void CMooreMachine::OnMinimizeEnd(const Table &table, const Dictionary &classesByState)
{
	std::map<size_t, IdList> statesByClass;

	for (size_t i = 0; i < table[1].size(); ++i)
	{
		const auto &newClass = classesByState.find(table[1][i]);
		auto &classList = statesByClass[newClass->second];
		classList.push_back(newClass->first);
	}

	Table newTable = Table(table.size(), IdList(statesByClass.size()));
	size_t tableColl = 0;

	for (const auto &tableClass : statesByClass)
	{
		newTable[0][tableColl] = m_classesByState.find(tableClass.second.front())->second;
		newTable[1][tableColl] = tableClass.first;
		++tableColl;
	}

	for (size_t i = 0; i < newTable[1].size(); ++i)
	{
		const auto &state = statesByClass.at(newTable[1][i]).front();

		for (size_t j = 2; j < newTable.size(); ++j)
		{
			const auto &transferState = m_transfersByState.at(state)[j - 2];
			newTable[j][i] = classesByState.at(transferState);
		}
	}

	m_table = newTable;
	m_classesByState = classesByState;
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