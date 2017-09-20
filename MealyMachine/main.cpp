#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "CMealyTable.h"
#include "CDotWriter.h"

namespace
{
	const int ARGUMENTS_COUNT = 1;
	const std::string INSTANCE_DOT_NAME = "instance.dot";
	const std::string MINIMIZE_DOT_NAME = "mininmize.dot";
	const std::string WINDOW_NAME = "Mealy machines";
	const int WINDOW_WIDTH = 1024;
	const int WINDOW_HEIGHT = 480;
}

CMealyTable CreateTable(const std::string &tableFilename);
void CreateDotFiles(const CMealyTable &table);
void Draw();

int main(int argc, char* argv[])
{
	try
	{
		if (argc < ARGUMENTS_COUNT)
		{
			throw new std::invalid_argument("Invalid arguments count.\nUse: MealyMachine.exe <table.xml>");
		}

		CMealyTable table = CreateTable(argv[0]);
		CreateDotFiles(table);
		Draw();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

CMealyTable CreateTable(const std::string &tableFilename)
{
	tinyxml2::XMLDocument xmlTable;

	try
	{
		xmlTable.LoadFile(tableFilename.c_str());
	}
	catch (const std::exception &e)
	{
		std::string msg = e.what();
		throw new std::invalid_argument("Can not load xml file:\n" + msg);
	}

	return CMealyTable(xmlTable);
}

void CreateDotFiles(const CMealyTable &table)
{
	(void)table;
}

void Draw()
{
	sf::RenderWindow window(
		sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		WINDOW_NAME,
		sf::Style::Titlebar | sf::Style::Close
	);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::White);
		window.display();
	}
}