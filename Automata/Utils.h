#include "IMachine.h"
#include "CDotWriter.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

namespace Utils
{
	using Matrix = std::vector<std::vector<size_t>>;
	
	std::string ToImage(const IMachine &machine, const std::string &fileName);
	bool RunProcess(const std::string &command);
	std::string MatrixToStr(const Matrix &matrix);

	template<typename T> std::vector<T> RowToVect(std::ifstream &input)
	{
		std::vector<T> result;
		T element;

		while (input.peek() != '\n' && !input.eof() && input >> element)
		{
			result.push_back(element);
		}

		input.get();

		return result;
	}
}
