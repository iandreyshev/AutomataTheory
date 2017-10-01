#pragma once
#include <set>
#include <map>
#include <fstream>
#include <algorithm>
#include <sstream>

#include "CDotWriter.h"
#include "Utils.h"

class CMooreMachine : public IMachine
{
public:
	CMooreMachine() = delete;
	CMooreMachine(std::ifstream &input);

	bool Minimize() override;
	std::string ToString() const override;
	std::string ToDotString() const override;
private:
	void InitStates(const IdList &outs, const IdList &states);
	void InitFullTable(const IdList &outs, const IdList &states, const Table &transfers);
	void InitTransfersMap();

	Table ZeroMinimize();
	void NextMinimize(Table &table, Dictionary &states);
	void CreateNewTable(Table &table, Dictionary &states);

	void Cleanup();

	Dictionary m_classesByStates;
	DictionaryList m_transfersByState;
	Table m_table;
};