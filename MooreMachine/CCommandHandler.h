#pragma once

#include "Utils.h"
#include <string>
#include <functional>
#include <fstream>
#include <iostream>
#include <map>

namespace
{
	const std::string CONSOLE_PREFIX = "";
	const std::string EXTI_COMMAND = "exit";
}

class CCommandHandler
{
public:
	CCommandHandler() = delete;
	CCommandHandler(std::istream &input);

	void HandleCommand() const;
private:
	std::istream &m_input;
	std::map<std::string, std::function<void()>> m_commands = {
		{ "help", std::bind(&CCommandHandler::PrintHelp, this) },
		{ "minmoore", std::bind(&CCommandHandler::MinimizeMoore, this) }
	};

	void Write(const std::string &message) const;
	bool PrintHelp() const;
	bool MinimizeMoore() const;
};