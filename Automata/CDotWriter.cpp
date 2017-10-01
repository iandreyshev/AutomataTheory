#include "CDotWriter.h"

CDotWriter::CDotWriter(std::ostream & out)
	:m_out(out)
{
	m_out << "digraph G{\n";
}

CDotWriter::~CDotWriter()
{
	m_out << "}\n";
}

void CDotWriter::PrintEdge(size_t from, size_t to, const std::string &label)
{
	m_out << from << "->" << to << " [label=\"" << label << " \"];\n";
}

void CDotWriter::PrintVertex(size_t index, const std::string &label, StateType type)
{
	m_out << index << " [";
	m_out << "shape=\"" << GetShape(type) << "\"";
	m_out << "label=\"" << label << "\"];\n";
}

std::string CDotWriter::GetShape(StateType type)
{
	switch (type)
	{
	case StateType::Initial:
		return "circle";
	case StateType::Nonterminal:
		return "box";
	case StateType::Terminal:
		return "doublecircle";
	}

	return std::string();
}