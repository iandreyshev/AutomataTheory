#include "CMealyMachine.h"

namespace
{
	const char HASH_SEPARATOR = '|';
	const size_t MIN_EQU_CLASS = 1;

	auto throw_invalid_arg_if = [](bool predicate, const auto &message) {
		if (predicate) throw std::invalid_argument(message);
	};
}

CMealyMachine::CMealyMachine(std::ifstream &input)
{
	auto states = Machine::read_moore_line<size_t>(input);

	Table transfers;
	Table transfersOutputs;
	auto transferRow = Machine::read_mealy_line<size_t>(input);

	while (!transferRow[0].empty() && !transferRow[1].empty())
	{
		transfers.push_back(transferRow[0]);
		transfersOutputs.push_back(transferRow[1]);
		transferRow = Machine::read_mealy_line<size_t>(input);
	}

	InitStates(states);
	InitFullTable(transfers, states);	
	InitOutputsMap(transfersOutputs, states);
	InitTransfersMap();
	InitEquClasses();
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
	for (const auto &state : states)
	{
		m_outsByState.insert(std::make_pair(state, std::vector<size_t>()));
	}

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

void CMealyMachine::InitEquClasses()
{
	auto to_hash = [&](size_t state) {
		std::string result;
		for (const auto &out : m_outsByState.at(state))
			result += HASH_SEPARATOR + std::to_string(out);
		return result;
	};

	std::unordered_map<std::string, size_t> hashes;
	size_t equClass = MIN_EQU_CLASS;

	for (size_t i = 0; i < m_table[1].size(); ++i)
	{
		const auto &state = m_table[1][i];
		const auto &hash = to_hash(state);

		if (hashes.find(hash) != hashes.end())
		{
			m_classesByState.at(state) = hashes.at(hash);
			m_table[0][i] = hashes.at(hash);
			continue;
		}

		m_classesByState.at(state) = equClass;
		m_table[0][i] = equClass;
		hashes.insert(std::make_pair(hash, equClass));
		++equClass;
	}
}

void CMealyMachine::OnMinimizeEnd(const Table &table, const Dictionary &classesByState)
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

std::string CMealyMachine::ToDotString() const
{
	std::stringstream stream;
	CDotWriter writer(stream);

	for (size_t i = 0; i < m_table.front().size(); ++i)
	{
		size_t inputIndex = 0;
		const auto state = m_table[1][i];
		const auto label = Machine::STATE_NAME + std::to_string(state);
		writer.PrintVertex(state, label, StateType::Initial);

		for (size_t j = 2; j < m_table.size(); ++j)
		{
			const auto &out = m_outsByState.at(state)[inputIndex];
			const auto &edgeLabel =
				Machine::INPUT_NAME + std::to_string(j - 1) + " / " +
				Machine::OUT_NAME + std::to_string(out);
			writer.PrintEdge(state, m_table[j][i], edgeLabel);
			++inputIndex;
		}
	}

	writer.~CDotWriter();
	return stream.str();
}