#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using DrawList = std::vector<sf::RectangleShape>;

class CGraphVizualizer
{
public:
	CGraphVizualizer() = delete;
	static void Draw(const std::string &graph);
	static void Draw(const std::string &firstGraph, const std::string &secondGraph);

private:
	static sf::RectangleShape GetShape(const std::string &name, const sf::Vector2f &center, sf::Texture &texture);
	static void DrawingLoop(sf::RenderWindow &window, const DrawList &toDraw);
	static void ResizeGraph(sf::RectangleShape &graph);
};