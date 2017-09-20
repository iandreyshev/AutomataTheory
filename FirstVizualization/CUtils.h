#pragma once

#include <string>

class CUtils
{
public:
	CUtils() = delete;

	static bool RunProcess(std::string const& command);
};