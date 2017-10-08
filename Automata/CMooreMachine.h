#pragma once

#include "CDotWriter.h"
#include "Utils.h"

class CMooreMachine : public CMachine
{
public:
	CMooreMachine() = delete;
	CMooreMachine(std::ifstream &input);

	bool Minimize() override;
	std::string ToDotString() const override;

protected:
	void OnCleanup() override;

private:
	void InitStates(const IdList &outs, const IdList &states);
	void InitFullTable(const IdList &outs, const IdList &states, const Table &transfers);
	void InitTransfersMap();
	Table ZeroMinimize();
	void CreateNewTable(Table &table, Dictionary &states);

	Dictionary m_classesByState;
	DictionaryList m_transfersByState;
};