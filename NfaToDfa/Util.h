#pragma once
#include <string>

namespace Util
{
	void TrimString(std::string &str)
	{
		while (isspace(*str.begin())) str.erase(0, 1);
		while (isspace(*--str.end())) str.erase(str.length() - 1, 1);
	}
}