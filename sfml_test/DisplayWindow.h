#pragma once
#include "SFML\Graphics.hpp"
#include <functional>

class DisplayWindow
{
public:
	DisplayWindow(int width, int height, char window_text[]);
	~DisplayWindow();
	void update(std::function<void(double)>&& f);
	void loop();
private:
	std::function<void(double)> updateCallback;
	sf::RenderWindow* window;
};

