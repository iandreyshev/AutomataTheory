#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class CGraphVizualizer
{
public:
	CGraphVizualizer() = delete;
	CGraphVizualizer(const std::string &instanceName, const std::string &minimizeName);

	void Draw();

private:
	sf::Texture m_firstTexture;
	sf::Texture m_secondTexture;

	sf::RectangleShape m_firstGraph;
	sf::RectangleShape m_secondGraph;

	void DrawingLoop(sf::RenderWindow &window);
	void ResizeGraph(sf::RectangleShape &graph);
};