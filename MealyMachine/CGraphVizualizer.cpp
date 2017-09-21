#include "CGraphVizualizer.h"
#include "CUtils.h"

namespace
{
	const sf::Vector2i WINDOW_SIZE = { 1024, 640 };
	const sf::Vector2f FIRST_GRAPH_CENTER = {
		(float)WINDOW_SIZE.x / 4, (float)WINDOW_SIZE.y / 2
	};
	const sf::Vector2f SECOND_GRAPH_CENTER = {
		3 * FIRST_GRAPH_CENTER.x, FIRST_GRAPH_CENTER.y
	};
	const float IMAGE_FACTOR = 0.95f;
}

CGraphVizualizer::CGraphVizualizer(
	const std::string &before,
	const std::string &after
)
{
	auto init_graph = [&](
		const std::string &imgName,
		sf::Texture &texture,
		sf::RectangleShape &shape,
		const sf::Vector2f &center)
	{
		if (!texture.loadFromFile(imgName))
		{
			throw std::invalid_argument("Can not load graph image: " + imgName);
		}
		shape.setTexture(&texture);
		ResizeGraph(shape);
		sf::Vector2f offset = shape.getSize() * 0.5f;
		shape.setPosition(center - offset);
	};

	init_graph(before, m_firstTexture, m_firstGraph, FIRST_GRAPH_CENTER);
	init_graph(after, m_secondTexture, m_secondGraph, SECOND_GRAPH_CENTER);
}

void CGraphVizualizer::Draw()
{
	sf::VideoMode mode = sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y);
	sf::RenderWindow window(mode, "", sf::Style::Titlebar | sf::Style::Close);

	DrawingLoop(window);
}

void CGraphVizualizer::DrawingLoop(sf::RenderWindow &window)
{
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
		window.draw(m_firstGraph);
		window.draw(m_secondGraph);
		window.display();
	}
}

void CGraphVizualizer::ResizeGraph(sf::RectangleShape &graph)
{
	const sf::Vector2u& textureSize = graph.getTexture()->getSize();
	sf::Vector2f size({ (float)textureSize.x, (float)textureSize.y });
	const float& sizeFactor = size.x / size.y;
	graph.setSize(size);

	size.x = (size.x > WINDOW_SIZE.x / 2) ? WINDOW_SIZE.x / 2 : size.x;
	size.x *= IMAGE_FACTOR;
	size.y = size.x / sizeFactor;

	size.y = (size.y > WINDOW_SIZE.y) ? WINDOW_SIZE.y : size.y;
	size.y *= IMAGE_FACTOR;
	size.x = size.y * sizeFactor;

	graph.setSize(size);
}