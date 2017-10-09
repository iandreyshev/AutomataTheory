#pragma once

#include <set>
#include <map>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <unordered_map>

namespace Machine
{
	const std::string STATE_NAME = "s";
	const std::string OUT_NAME = "o";
	const std::string INPUT_NAME = "x";
	const size_t HEADER_ROWS = 2;
	const size_t MIN_STATES_COUNT = 1;
	const size_t MIN_TRANSFERS_COUNT = 1;

	template<typename T> std::vector<T> read_moore_line(std::ifstream &input)
	{
		std::vector<T> result;
		T state;

		while (input.peek() != '\n' && !input.eof() && input >> state)
		{
			result.push_back(state);
		}

		input.get();

		return result;
	}
	template<typename T> std::vector<std::vector<T>> read_mealy_line(std::ifstream &input)
	{
		std::vector<std::vector<T>> result(2);
		char separator;
		T state;
		T output;

		T inputId;
		input >> inputId;

		while (input.peek() != '\n' && !input.eof() &&
			input >> state &&
			input >> separator &&
			separator == '/' &&
			input >> output)
		{
			result[0].push_back(state);
			result[1].push_back(output);
		}

		input.get();

		return result;
	}
}

using IdList = std::vector<size_t>;
using Table = std::vector<IdList>;
using Dictionary = std::unordered_map<size_t, size_t>;
using DictionaryList = std::unordered_map<size_t, IdList>;

class CMachine
{
public:
	virtual bool Minimize() = 0;
	virtual std::string ToDotString() const = 0;
	void Cleanup();

protected:
	Table ZeroMinimize(const Dictionary &classesByState) const;
	void NextMinimize(Table &table, Dictionary &states);
	virtual void OnCleanup() = 0;

	Table m_table;
};