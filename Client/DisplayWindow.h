#pragma once
#include "SFML\Graphics.hpp"
#include <functional>
#include <iostream>
#include <string>
#include <fstream>

class DisplayWindow
{
public:
	DisplayWindow(int width, int height, char window_text[]);
	~DisplayWindow();
	void update(std::function<void(double)>&& f);
	void loop();

	void printText(std::string mytext, int x, int y);
	void printText(std::string mytext, int x, int y, int size);
	void printText(std::string mytext, int x, int y, int size, sf::Color color);
	void printText(std::string mytext, int x, int y, int size, sf::Color color, std::string font_name);

	void drawGraph();
	void updateTH(int temp, int humid);
	void button();
	bool connect = false;
	int temp = 0, humid = 0;
private:
	std::function<void(double)> updateCallback;
	sf::RenderWindow* window;
	bool focus = true;
	bool lmb_pressed = false;
	bool button_action = false;
};

