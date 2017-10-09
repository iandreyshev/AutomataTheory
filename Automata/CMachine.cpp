#include "CMachine.h"

namespace
{
	const char HASH_SEPARATOR = '|';
}

void CMachine::NextMinimize(Table &table, Dictionary &states)
{
	auto to_hash = [&](size_t coll) -> std::string {
		const auto &state = table[1][coll];
		std::string result = std::to_string(states.find(state)->second);
		for (size_t row = 2; row < table.size(); ++row)
			result += HASH_SEPARATOR + std::to_string(table[row][coll]);
		return result;
	};

	std::unordered_map<std::string, size_t> stateIndexesByHash;
	std::vector<std::vector<size_t>> stateIndexes;

	auto add_hash_if = [&](const std::string hash, size_t newState) {
		if (stateIndexesByHash.find(hash) != stateIndexesByHash.end())
		{
			const auto statesIndex = stateIndexesByHash.find(hash)->second;
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
			const auto instanceTransfer = m_table[i][j];
			table[i][j] = states.find(instanceTransfer)->second;
		}
	}
}

Table CMachine::ZeroMinimize(const Dictionary &classesByState) const
{
	Table result = m_table;

	for (size_t i = 2; i < result.size(); ++i)
	{
		for (size_t j = 0; j < result[i].size(); ++j)
		{
			const auto instanceTransfer = m_table[i][j];
			result[i][j] = classesByState.find(instanceTransfer)->second;
		}
	}

	return result;
}

void CMachine::Cleanup()
{
	OnCleanup();
	m_table.clear();
}