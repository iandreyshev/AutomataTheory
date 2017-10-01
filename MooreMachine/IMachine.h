#pragma once
#include <string>

class IMachine
{
public:
	virtual ~IMachine() = default;

	virtual bool Minimize() = 0;
	virtual std::string ToString() const = 0;
	virtual std::string ToDotString() const = 0;
};