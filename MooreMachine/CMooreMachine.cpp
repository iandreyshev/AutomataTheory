#include "CMooreMachine.h"

namespace
{
	const char CSV_SEPARATOR = ';';
}

CMooreMachine::CMooreMachine(std::ifstream &input)
{
	std::string outputStr;
	std::string stateStr;
	getline(input, outputStr);
	getline(input, stateStr);

	auto outputs = CUtils::SplitString(outputStr, CSV_SEPARATOR);
	auto states = CUtils::SplitString(stateStr, CSV_SEPARATOR);

	for (size_t i = 1; i < states.size(); ++i)
	{
		size_t stateNum = std::atoi(states[i].c_str());
		size_t outNum = std::atoi(outputs[i].c_str());
		m_table.states.insert(std::make_pair(stateNum, outNum));
	}

	std::string inputStr;
	while (getline(input, inputStr))
	{
		auto inputRow = CUtils::SplitString(inputStr, CSV_SEPARATOR);
		size_t inputId = std::atoi(inputRow[0].c_str());
		for (size_t i = 1; i < inputRow.size(); ++i)
		{
			if (m_table.input.find(inputId) == m_table.input.end())
			{
				m_table.input.insert(std::make_pair(inputId, std::vector<size_t>()));
			}

			size_t stateId = std::atoi(inputRow[i].c_str());
			m_table.input.find(inputId)->second.push_back(stateId);
		}
	}
}

bool CMooreMachine::Minimize()
{
	MooreTable zeroEquTable = m_table;
	bool isMinimize = ToZeroEquClass(zeroEquTable);

	while (isMinimize)
	{
		isMinimize = ToNextEquClass(m_table);
	}

	return isMinimize;
}

bool CMooreMachine::ToZeroEquClass(MooreTable &table)
{
	return true;
}

bool CMooreMachine::ToNextEquClass(MooreTable &table)
{
	return true;
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