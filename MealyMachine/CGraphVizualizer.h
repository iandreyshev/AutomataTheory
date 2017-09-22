#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using DrawList = std::vector<sf::RectangleShape>;

class CGraphVizualizer
{
public:
	void Draw(const std::string &graph);
	void Draw(const std::string &firstGraph, const std::string &secondGraph);

private:
	sf::RectangleShape GetShape(const std::string &name, const sf::Vector2f &center, sf::Texture &texture);
	void DrawingLoop(sf::RenderWindow &window, const DrawList &toDraw);
	void ResizeGraph(sf::RectangleShape &graph);
};