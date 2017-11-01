#pragma once

namespace
{
	const char END_SYMBOL = '#';
}

class CRule
{
public:
	CRule(char terminal);
	CRule(char terminal, char state);

	bool IsTerminal() const;
	static bool IsTerminal(char symbol);
	static bool IsState(char symbol);
	static bool IsEnd(char symbol);

private:
	bool m_isTerminal;
	char m_state;
	char m_terminal;

};