#include "CMealyMachine.h"

namespace
{
	const char* DEST_ATRIBUTE = "jump";
	const char* OUT_ATTRIBUTE = "out";
}

CMealyMachine::CMealyMachine(const tinyxml2::XMLDocument &xmlTable)
{
	Cleanup();

	const tinyxml2::XMLElement* root = xmlTable.FirstChildElement();
	XMLElementCollection inCollection = CUtils::GetAllChilds(root);

	InitInputAlphabet(inCollection);
	InitStatesCollection(inCollection);
	InitTable(inCollection);
}

CMealyMachine::CMealyMachine(const MealyTable &table)
{
	(void)table;
}

CMealyMachine CMealyMachine::ToMinimize() const
{
	return CMealyMachine(m_table);
}

std::string CMealyMachine::ToDotString() const
{
	return "";
}

// Collect all inputs and check duplicate
void CMealyMachine::InitInputAlphabet(const XMLElementCollection &inCollection)
{
	for (auto &input : inCollection)
	{
		const std::string &value = input->Value();
		if (m_table.find(value) != m_table.end())
		{
			throw std::invalid_argument(
				"Invalid table formatting - duplicate input '" + value + "'.");
		}
		m_table.insert(std::make_pair(value, MealyNodesVec()));
	}
}

// Read all states and collect them
void CMealyMachine::InitStatesCollection(const XMLElementCollection &inCollection)
{
	size_t stateIndex = 0;

	for (auto &input : inCollection)
	{
		XMLElementCollection allInputStates = CUtils::GetAllChilds(input);
		for (auto &state : allInputStates)
		{
			const std::string &stateName = state->Value();
			if (m_statesMap.find(stateName) == m_statesMap.end())
			{
				m_statesMap.insert(std::make_pair(stateName, stateIndex));
				stateIndex++;
			}
		}
	}
}

void CMealyMachine::InitTable(const XMLElementCollection &inCollection)
{
	for (auto &input : inCollection)
	{
		std::string inputValue = input->Value();
		XMLElementCollection allInputStates = CUtils::GetAllChilds(input);
		for (auto &state : allInputStates)
		{
			const std::string &stateName = state->Value();
			const std::string &destState = state->Attribute(DEST_ATRIBUTE);
			const std::string &output = state->Attribute(OUT_ATTRIBUTE);

			if (m_statesMap.find(destState) == m_statesMap.end())
			{
				throw std::invalid_argument(
					"Invalid destination state '" + destState + "'.");
			}
			const size_t &currIndex = m_statesMap.find(stateName)->second;
			const size_t &destIndex = m_statesMap.find(destState)->second;
			const MealyNode &newNode = { currIndex, destIndex, output };
			m_table.find(inputValue)->second.push_back(newNode);
		}
	}
}

void CMealyMachine::Cleanup()
{
	m_table.clear();
	m_statesMap.clear();
}