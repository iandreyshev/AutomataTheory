#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "libs/tinyxml2/tinyxml2.h"

using XMLElementCollection = std::vector<const tinyxml2::XMLElement*>;
using Matrix = std::vector<std::vector<size_t>>;

class CUtils
{
public:
	CUtils() = delete;

	static bool RunProcess(const std::string &command);
	static XMLElementCollection GetAllChilds(const tinyxml2::XMLElement* parent);
	static std::vector<std::string> SplitString(const std::string &str, char separator);
	static std::string MatrixToStr(const Matrix &matrix);
};