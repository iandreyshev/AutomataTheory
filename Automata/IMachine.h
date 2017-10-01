#pragma once
#include <string>
#include <unordered_map>

class IMachine
{
public:
	virtual ~IMachine() = default;

	virtual bool Minimize() = 0;
	virtual std::string ToString() const = 0;
	virtual std::string ToDotString() const = 0;
};

using IdList = std::vector<size_t>;
using Table = std::vector<IdList>;
using Dictionary = std::unordered_map<size_t, size_t>;
using DictionaryList = std::unordered_map<size_t, IdList>;