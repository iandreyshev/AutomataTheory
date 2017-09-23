#include "CMealyMachine.h"
#include <boost/algorithm/string.hpp>

namespace
{
	const char SEPARATOR = ',';
	const char* START_ATTRIBUTE = "start";
	const char* END_ATTRIBUTE = "end";
	const char* DEST_ATRIBUTE = "dest";
	const char* OUT_ATTRIBUTE = "out";
}

CMealyMachine::CMealyMachine(const tinyxml2::XMLDocument &xmlTable)
{
	Cleanup();

	const tinyxml2::XMLElement* root = xmlTable.FirstChildElement();
	XMLElementCollection statesNodes = CUtils::GetAllChilds(root);

	InitStates(statesNodes);
	InitTable(statesNodes);
	InitTerminals(root);
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
	std::stringstream stream;
	CDotWriter writer(stream);

	for (auto &state : m_states)
	{
		StateType type = GetStateType(state.second);
		writer.PrintVertex(state.second, state.first, type);
	}

	for (auto &state : m_table)
	{
		const auto &stateInputs = state.second;

		for (auto &input : stateInputs)
		{
			const auto &edge = input.second;
			const auto &label = "[" + input.first + ", " + edge.output + "]";
			writer.PrintEdge(state.first, edge.destIndex, label);
		}
	}

	writer.~CDotWriter();
	return stream.str();
}

void CMealyMachine::InitTerminals(const tinyxml2::XMLElement* root)
{
	auto get_states = [&](const std::string &attribute, std::set<size_t> &collection) {
		const auto &attributeStr = root->Attribute(attribute.c_str());
		std::vector<std::string> values = CUtils::Split(attributeStr, SEPARATOR);
		if (values.empty())
		{
			throw std::invalid_argument("The terminal states is not set.");
		}

		for (auto val : values)
		{
			if (m_states.find(val) == m_states.end())
			{
				throw std::invalid_argument(
					"Invalid arguments in " + attribute + " property.");
			}
			collection.insert(m_states.at(val));
		}
	};

	get_states(START_ATTRIBUTE, m_start);
	get_states(END_ATTRIBUTE, m_end);
}

// Read all states and collect them
void CMealyMachine::InitStates(const XMLElementCollection &statesNodes)
{
	size_t stateIndex = 0;

	for (auto &state : statesNodes)
	{
		const std::string &stateName = state->Value();
		if (m_states.find(stateName) != m_states.end())
		{
			throw std::invalid_argument("States duplicated.");
		}

		m_states.insert(std::make_pair(stateName, stateIndex));
		stateIndex++;
	}
}

// Collect all inputs and check duplicate
void CMealyMachine::InitTable(const XMLElementCollection &statesNodes)
{
	for (auto &state : statesNodes)
	{
		for (auto &inputNode : CUtils::GetAllChilds(state))
		{
			const auto &inputName = inputNode->Value();
			const auto &stateIndex = GetStateIndex(state->Value());

			m_table.insert(std::make_pair(stateIndex, MealyInput()));
			auto &stateEdges = m_table.at(stateIndex);

			if (stateEdges.find(inputName) != stateEdges.end())
			{
				throw std::invalid_argument("The machine is not deterministic.");
			}
			const auto &destName = inputNode->Attribute(DEST_ATRIBUTE);
			const auto &output = inputNode->Attribute(OUT_ATTRIBUTE);

			if (m_states.find(destName) == m_states.end())
			{
				throw std::invalid_argument("Invalid destination state.");
			}

			MealyEdge edge = { m_states.at(destName), output };
			stateEdges.insert(std::make_pair(inputName, edge));
		}
	}
}

size_t CMealyMachine::GetStateIndex(const std::string &name) const
{
	if (m_states.find(name) == m_states.end())
	{
		throw std::invalid_argument("Can not find state by name.");
	}

	return m_states.find(name)->second;
}

StateType CMealyMachine::GetStateType(size_t index) const
{
	if (m_start.find(index) != m_start.end())
	{
		return StateType::Initial;
	}
	else if (m_end.find(index) != m_end.end())
	{
		return StateType::Terminal;
	}

	return StateType::Nonterminal;
}

void CMealyMachine::Cleanup()
{
	m_table.clear();
	m_states.clear();
	m_start.clear();
	m_end.clear();
}