#pragma once
#include <string>
#include <unordered_map>

using IdList = std::vector<size_t>;
using Table = std::vector<IdList>;
using Dictionary = std::unordered_map<size_t, size_t>;
using DictionaryList = std::unordered_map<size_t, IdList>;

class CMachine
{
public:
	virtual bool Minimize() = 0;
	virtual std::string ToDotString() const = 0;

protected:
	Dictionary m_classesByStates;
	DictionaryList m_transfersByState;
	Table m_table;

	void NextMinimize(Table &table, Dictionary &states);
	void Cleanup();
private:

};