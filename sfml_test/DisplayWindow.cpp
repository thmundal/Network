#include "DisplayWindow.h"



DisplayWindow::DisplayWindow(int width, int height, char window_text[])
{
	window =  new sf::RenderWindow(sf::VideoMode(width, height), window_text);
	window->display();
}

void DisplayWindow::update(std::function<void(double)>&& cb) {
	updateCallback = cb;
}

void DisplayWindow::loop() {
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event))
		{
			updateCallback(0.0);

			if (event.type == sf::Event::Closed)
				window->close();

		}
	}
}

DisplayWindow::~DisplayWindow()
{
	delete window;
}
