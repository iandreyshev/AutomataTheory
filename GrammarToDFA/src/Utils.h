#include "CDotWriter.h"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

namespace Utils
{
	using Matrix = std::vector<std::vector<size_t>>;
	
	std::string ToImage(const std::string &dotStr, const std::string &fileName);
	bool RunProcess(const std::string &command);
	void TrimString(std::string &str);
}
