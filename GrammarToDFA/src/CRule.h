#pragma once

class CRule
{
public:
	static bool IsTerminal(char symbol);
	static bool IsState(char symbol);

	CRule(char terminal);
	CRule(char first, char second);

	bool IsTerminal() const;
	char GetTerminal() const;
	char GetState() const;

private:
	bool m_isTerminal;
	char m_state;
	char m_terminal;

};