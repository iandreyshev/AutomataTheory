#include "CPrinter.h"
#include "CUtils.h"
#include <cstdarg>

namespace
{
	const sf::Vector2f WINDOW_SIZE = { 1024, 640 };
	const sf::Vector2f WINDOW_CENTER = WINDOW_SIZE * 0.5f;
	const sf::Vector2f FIRST_GRAPH_CENTER = {
		WINDOW_SIZE.x / 4, WINDOW_SIZE.y / 2
	};
	const sf::Vector2f SECOND_GRAPH_CENTER = {
		3 * FIRST_GRAPH_CENTER.x, FIRST_GRAPH_CENTER.y
	};
}

void CPrinter::Draw(const std::string &graph)
{
	sf::VideoMode mode = sf::VideoMode((unsigned)WINDOW_SIZE.x, (unsigned)WINDOW_SIZE.y);
	sf::RenderWindow window(mode, "", sf::Style::Titlebar | sf::Style::Close);

	sf::Texture texture;
	DrawingLoop(window, { GetShape(graph, WINDOW_CENTER, texture) });
}

void CPrinter::Draw(const std::string &first, const std::string &second)
{
	sf::VideoMode mode = sf::VideoMode((unsigned)WINDOW_SIZE.x, (unsigned)WINDOW_SIZE.y);
	sf::RenderWindow window(mode, "", sf::Style::Titlebar | sf::Style::Close);

	sf::Texture firstTexture;
	sf::Texture secondTexture;
	DrawingLoop( window, {
			GetShape(first, FIRST_GRAPH_CENTER, firstTexture),
			GetShape(second, SECOND_GRAPH_CENTER, secondTexture)
		});
}

sf::RectangleShape CPrinter::GetShape(
	const std::string &name,
	const sf::Vector2f &center,
	sf::Texture &texture)
{
	sf::RectangleShape shape;

	if (!texture.loadFromFile(name))
	{
		throw std::invalid_argument("Can not load graph image: " + name);
	}

	shape.setTexture(&texture);
	ResizeGraph(shape);
	const auto &offset = shape.getSize() * 0.5f;
	shape.setPosition(center - offset);
	return shape;
}


void CPrinter::DrawingLoop(sf::RenderWindow &window, const DrawList &toDraw)
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

		window.display();
		window.clear(sf::Color::White);
		for (auto &drawObject : toDraw)
		{
			window.draw(drawObject);
		}
	}
}

void CPrinter::ResizeGraph(sf::RectangleShape &graph)
{
	const auto& textureSize = graph.getTexture()->getSize();
	sf::Vector2f size((float)textureSize.x, (float)textureSize.y);
	const float& sizeFactor = size.x / size.y;
	graph.setSize(size);

	size.x = (size.x > WINDOW_SIZE.x / 2) ? WINDOW_SIZE.x / 2 : size.x;
	size.y = size.x / sizeFactor;

	size.y = (size.y > WINDOW_SIZE.y) ? WINDOW_SIZE.y : size.y;
	size.x = size.y * sizeFactor;

	graph.setSize(size);
}