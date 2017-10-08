#include "CMealyMachine.h"

namespace
{
	auto throw_invalid_arg_if = [](bool predicate, const auto &message) {
		if (predicate) throw std::invalid_argument(message);
	};
}

CMealyMachine::CMealyMachine(std::ifstream &input)
{
	auto states = Machine::read_moore_line<size_t>(input);
	InitStates(states);

	Table transfers;
	Table transfersOutputs;
	auto transferRow = Machine::read_mealy_line<size_t>(input);

	while (!transferRow[0].empty() && !transferRow[1].empty())
	{
		transfers.push_back(transferRow[0]);
		transfersOutputs.push_back(transferRow[1]);
		transferRow = Machine::read_mealy_line<size_t>(input);
	}

	InitFullTable(transfers, states);
	InitOutputsMap(transfersOutputs, states);
	InitTransfersMap();
}

void CMealyMachine::InitStates(const IdList &states)
{
	throw_invalid_arg_if(
		states.size() < Machine::MIN_STATES_COUNT,
		"States count less than " + std::to_string(Machine::MIN_STATES_COUNT) + ".");

	for (size_t i = 0; i < states.size(); ++i)
	{
		throw_invalid_arg_if(
			m_classesByState.find(states[i]) != m_classesByState.end(),
			"Duplicate states in header not allowed.");
		m_classesByState.insert(std::make_pair(states[i], 0));
		m_outsByState.insert(std::make_pair(states[i], std::vector<size_t>()));
	}
}

void CMealyMachine::InitFullTable(const Table &transfers, const IdList &states)
{
	throw_invalid_arg_if(
		transfers.size() < Machine::MIN_TRANSFERS_COUNT,
		"Transfers less than " + std::to_string(Machine::MIN_TRANSFERS_COUNT));

	m_table.push_back(std::vector<size_t>(states.size()));
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

void CMealyMachine::InitTransfersMap()
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

void CMealyMachine::InitOutputsMap(const Table &transfersOutputs, const IdList &states)
{
	for (const auto &transfersRow : transfersOutputs)
	{
		throw_invalid_arg_if(
			transfersRow.size() != states.size(),
			"Invalid outputs count");

		for (size_t i = 0; i < transfersRow.size(); ++i)
		{
			m_outsByState.at(states[i]).push_back(transfersRow[i]);
		}
	}
}

void CMealyMachine::CreateNewTable()
{

}

bool CMealyMachine::Minimize()
{
	return false;
}

std::string CMealyMachine::ToDotString() const
{
	return "";
}

void CMealyMachine::OnCleanup()
{
	m_classesByState.clear();
	m_outsByState.clear();
	m_transfersByState.clear();
}