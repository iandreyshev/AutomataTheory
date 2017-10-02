#pragma once
#include <set>
#include <map>
#include <fstream>
#include <algorithm>
#include <sstream>

#include "CDotWriter.h"
#include "Utils.h"

class CMooreMachine : public CMachine
{
public:
	CMooreMachine() = delete;
	CMooreMachine(std::ifstream &input);

	bool Minimize() override;
	std::string ToDotString() const override;
private:
	void InitStates(const IdList &outs, const IdList &states);
	void InitFullTable(const IdList &outs, const IdList &states, const Table &transfers);
	void InitTransfersMap();

	Table ZeroMinimize();
	void CreateNewTable(Table &table, Dictionary &states);
};