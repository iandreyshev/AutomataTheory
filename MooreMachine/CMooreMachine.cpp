#include "CMooreMachine.h"

namespace
{
	const char CSV_SEPARATOR = ';';
	const size_t HEADER_ROWS = 2;
	const size_t MIN_STATES_COUNT = 1;
	const size_t MIN_TRANSFERS_COUNT = 1;
}

CMooreMachine::CMooreMachine(std::ifstream &input)
{
	auto row_to_vect = [&]() -> std::vector<size_t> {
		std::vector<size_t> result;
		std::string str;
		getline(input, str);
		auto rowIds = CUtils::SplitString(str, CSV_SEPARATOR);
		for (auto idStr : rowIds) result.push_back(std::atoi(idStr.c_str()));
		return result;
	};

	auto outputs = row_to_vect();
	auto states = row_to_vect();
	InitHeader({ outputs, states });

	Table transfers;
	auto transferRow = row_to_vect();

	while (!transferRow.empty())
	{
		transfers.push_back(transferRow);
		transferRow = row_to_vect();
	}

	InitTransfers(transfers);
}

void CMooreMachine::InitHeader(const Table &tableHeader)
{
	auto throw_invalid_arg_if = [](bool predicate, const auto &message) {
		if (predicate) throw std::invalid_argument(message);
	};

	throw_invalid_arg_if(
		tableHeader.size() != HEADER_ROWS,
		"Invalid header size.");

	const auto &outs = tableHeader[0];
	const auto &states = tableHeader[1];

	throw_invalid_arg_if(
		outs.size() != states.size(),
		"States count not equal outputs count.");

	throw_invalid_arg_if(
		states.size() < MIN_STATES_COUNT,
		"States count less than " + std::to_string(MIN_STATES_COUNT) + ".");

	for (size_t i = 1; i < states.size(); ++i)
	{
		throw_invalid_arg_if(
			m_instStates.find(states[i]) != m_instStates.end(),
			"Duplicate states in header not allowed.");
		m_instStates.insert(std::make_pair(states[i], outs[i]));
	}
}

void CMooreMachine::InitTransfers(const Table &transfersTable)
{
	auto throw_invalid_arg_if = [](bool predicate, const auto &message) {
		if (predicate) throw std::invalid_argument(message);
	};

	throw_invalid_arg_if(
		transfersTable.size() < MIN_TRANSFERS_COUNT,
		"Transfers less than " + std::to_string(MIN_TRANSFERS_COUNT));
	
	size_t rowIndex = 0;
	for (auto transferRow : transfersTable)
	{
		const auto &transfersCount = transferRow.size() - 1;
		throw_invalid_arg_if(
			transfersCount < m_instStates.size(),
			"Transfers count less than states count.");
		m_transfer.push_back(std::vector<size_t>());

		for (size_t i = 1; i < transferRow.size(); ++i)
		{
			throw_invalid_arg_if(
				m_instStates.find(transferRow[i]) == m_instStates.end(),
				"Transfer state not found in states list.");
			m_transfer[rowIndex].push_back(transferRow[i]);
		}
		rowIndex++;
	}
}

bool CMooreMachine::ToMinimize()
{
	bool isMinimize = false;
	return isMinimize;
}

std::string CMooreMachine::ToDotString()
{
	return "";
}

std::string CMooreMachine::ToString()
{
	std::string result;
	return result;
}

void CMooreMachine::Cleanup()
{
	m_instStates.clear();
	m_transfer.clear();
}