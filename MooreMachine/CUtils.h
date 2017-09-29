#pragma once

#include <vector>
#include <string>
#include <iostream>

using Matrix = std::vector<std::vector<size_t>>;

class CUtils
{
public:
	CUtils() = delete;

	static bool RunProcess(const std::string &command);
	static std::vector<std::string> SplitString(const std::string &str, char separator);
	static std::string MatrixToStr(const Matrix &matrix);
};