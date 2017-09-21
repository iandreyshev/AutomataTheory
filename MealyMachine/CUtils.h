#pragma once

#include <string>
#include <iostream>

class CUtils
{
public:
	CUtils() = delete;

	static bool RunProcess(const std::string &command);
	static void Log(const std::string &message);
};