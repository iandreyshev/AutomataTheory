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
	
	void ToImage(const IMachine &machine, const std::string &fileName);
	static bool RunProcess(const std::string &command);
	static std::string MatrixToStr(const Matrix &matrix);
}
