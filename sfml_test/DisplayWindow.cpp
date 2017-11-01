#include "DisplayWindow.h"



DisplayWindow::DisplayWindow(int width, int height, char window_text[])
{
	sf::RenderWindow win(sf::VideoMode(width, height), window_text);
	window = &win;
	window->display();
	//sf::Event event;
	//while (window.pollEvent(event))
	//{
	//	if (event.type == sf::Event::Closed)
	//		window.close();
	//}
}


DisplayWindow::~DisplayWindow()
{
}
