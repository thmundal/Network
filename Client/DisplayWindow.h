#pragma once
#include "SFML\Graphics.hpp"
#include <functional>
#include <iostream>
#include <string>

class DisplayWindow
{
public:
	DisplayWindow(int width, int height, char window_text[]);
	~DisplayWindow();
	void update(std::function<void(double)>&& f);
	void loop();
	void printText(char text[], int x, int y);
	void printText(char text[], int x, int y, int size);
	void printText(char text[], int x, int y, int size, sf::Color color);
	void printText(char text[], int x, int y, int size, sf::Color color, std::string font_name);

private:
	std::function<void(double)> updateCallback;
	sf::RenderWindow* window;
};

