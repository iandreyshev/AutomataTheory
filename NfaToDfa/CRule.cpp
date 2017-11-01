#include "CRule.h"

CRule::CRule(char terminal)
{
	m_isTerminal = true;
	m_terminal = terminal;
}

CRule::CRule(char terminal, char state)
{
	m_isTerminal = false;
	m_terminal = terminal;
	m_state = state;
}

bool CRule::IsTerminal() const
{
	return m_isTerminal;
}

bool CRule::IsTerminal(char symbol)
{
	return IsEnd(symbol) || symbol >= 'a' && symbol <= 'z';
}

bool CRule::IsState(char symbol)
{
	return !IsTerminal(symbol) && symbol >= 'A' && symbol <= 'Z';
}

bool CRule::IsEnd(char symbol)
{
	return symbol == END_SYMBOL;
}
