#pragma once
#include <ostream>
#include <string>

enum StateType
{
	Initial,
	Nonterminal,
	Terminal
};

class CDotWriter
{
public:
	CDotWriter() = delete;
	CDotWriter(std::ostream &out);
	~CDotWriter();

	void PrintEdge(size_t from, size_t to, const std::string &label);
	void PrintVertex(size_t index, const std::string &label, StateType type);
private:
	std::ostream &m_out;

	std::string GetShape(StateType type);
};