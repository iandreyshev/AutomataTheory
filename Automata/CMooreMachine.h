#pragma once

#include "CDotWriter.h"
#include "Utils.h"

class CMooreMachine : public CMachine
{
public:
	CMooreMachine() = delete;
	CMooreMachine(std::ifstream &input);
	std::string ToDotString() const override;

protected:
	void OnMinimizeEnd(const Table &table, const Dictionary &classesByState);

private:
	void InitStates(const IdList &outs, const IdList &states);
	void InitFullTable(const IdList &outs, const IdList &states, const Table &transfers);
	void InitTransfersMap();

	DictionaryList m_transfersByState;
};


