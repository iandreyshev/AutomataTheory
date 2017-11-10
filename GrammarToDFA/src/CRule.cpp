#include "CRule.h"
#include <string>
#include <boost/format.hpp>

namespace
{
	const std::string INVALID_FOR_TERMINAL =
		"Character '%1%' is not valid for terminals. Use lowercase characters for this.";
	
	const std::string INVALID_FOR_STATE =
		"Character '%1%' is not valid for states. Use Uppercase characters for this.";
}

CRule::CRule(char terminal)
{
	if (!IsTerminal(terminal))
	{
		throw std::invalid_argument((boost::format(INVALID_FOR_TERMINAL) % terminal).str());
	}

	m_isTerminal = true;
	m_terminal = terminal;
}

CRule::CRule(char state, char terminal)
{
	if (!IsTerminal(terminal))
	{
		throw std::invalid_argument((boost::format(INVALID_FOR_TERMINAL) % terminal).str());
	}
	else if (!IsState(state))
	{
		throw std::invalid_argument((boost::format(INVALID_FOR_STATE) % terminal).str());
	}

	m_isTerminal = false;
	m_terminal = terminal;
	m_state = state;
}

bool CRule::IsTerminal() const
{
	return m_isTerminal;
}

char CRule::GetTerminal() const
{
	return m_terminal;
}

char CRule::GetState() const
{
	if (m_isTerminal)
	{
		throw std::logic_error("Can not return state from terminal rule");
	}
	return m_state;
}

bool CRule::IsTerminal(char symbol)
{
	return symbol >= 'a' && symbol <= 'z';
}

bool CRule::IsState(char symbol)
{
	return symbol >= 'A' && symbol <= 'Z';
}
