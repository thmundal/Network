#pragma once
#include "SFML\Graphics.hpp"

class DisplayWindow
{
public:
	DisplayWindow(int width, int height, char window_text[]);
	~DisplayWindow();
	void update(int temp, int hum);
private:
	sf::RenderWindow* window;
};

