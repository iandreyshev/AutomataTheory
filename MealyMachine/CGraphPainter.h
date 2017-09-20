#pragma once
#include <string>

class CGraphPainter
{
public:
	CGraphPainter() = delete;
	CGraphPainter(const std::string &instanceGraph, const std::string &minGraph)
	{
		(void)instanceGraph;
		(void)minGraph;
	}

	void Draw(int winWidth, int winHeight)
	{
		(void)winWidth;
		(void)winHeight;
	}

private:

};
