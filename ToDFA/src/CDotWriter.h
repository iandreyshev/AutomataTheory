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
	CDotWriter::CDotWriter();

	void PrintEdge(size_t from, size_t to, const std::string &label);
	void PrintVertex(size_t index, const std::string &label, StateType type);
	std::string Get() const;

private:
	std::string GetShape(StateType type) const;

	std::string m_out;

};