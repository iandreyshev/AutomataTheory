#pragma once

#include "CDotWriter.h"
#include "Utils.h"

class CMealyMachine : public CMachine
{
public:
	CMealyMachine() = delete;
	CMealyMachine(std::ifstream &input);
	std::string ToDotString() const override;

protected:
	void OnMinimizeEnd(const Table &table, const Dictionary &classesByState) override;

private:
	void InitStates(const IdList &states);
	void InitFullTable(const Table &transfers, const IdList &states);
	void InitTransfersMap();
	void InitOutputsMap(const Table &transfersOutputs, const IdList &states);
	void InitEquClasses();

	DictionaryList m_outsByState;
	DictionaryList m_transfersByState;
};

