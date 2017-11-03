#include "DisplayWindow.h"

#define WHITE sf::Color::White
#define BLACK sf::Color::Black
#define GREY sf::Color::Grey
#define RED sf::Color::Red
#define GREEN sf::Color::Green
#define BLUE sf::Color::Blue

DisplayWindow::DisplayWindow(int width, int height, char window_text[])
{
	window = new sf::RenderWindow(sf::VideoMode(width, height), window_text);
	window->display();
}

void DisplayWindow::button()
{
	int x_size = 200, y_size = 100;
	int x_pos = 25, y_pos = 595;

	sf::RectangleShape button;
	button.setOutlineColor(sf::Color(54, 59, 63));
	button.setOutlineThickness(3);
	button.setSize({ float(x_size), float(y_size) });
	button.setPosition({ float(x_pos), float(y_pos) });

	if (focus) {
		sf::Vector2i position = sf::Mouse::getPosition(*window);
		if ((position.x > x_pos && position.x < x_pos + x_size) && (position.y > y_pos && position.y < y_pos + y_size))
		{
			button.setFillColor(sf::Color(54, 59, 63));
			if (lmb_pressed)
			{
				button.setFillColor(BLACK);
				button_action = true;
			}
			if (!lmb_pressed && button_action)
			{
				connect = true;
				button_action = false;
			}
		}
		else
		{
			button.setFillColor(sf::Color(37, 41, 44));
			button_action = false;
		}
	}
	else
	{
		button.setFillColor(sf::Color(37, 41, 44));
	}
	window->draw(button);
	printText("Update!", x_pos + x_size / 4, y_pos + y_size / 3);
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

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				lmb_pressed = true;

			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
				lmb_pressed = false;

			if (event.type == sf::Event::Closed)
				window->close();

			else if (event.type == sf::Event::GainedFocus)
				focus = true;

			else if (event.type == sf::Event::LostFocus)
				focus = false;
		}
		window->clear(sf::Color(37, 41, 44));
		drawGraph();
		button();
		printText("Temperature: " + std::to_string(temp) + "C", 25, 175, 36, RED, "SairaSemiCondensed-Regular.ttf");
		printText("Humidity: " + std::to_string(humid) + "%", 25, 275, 36, BLUE, "SairaSemiCondensed-Regular.ttf");
		window->display();
	}
}

void DisplayWindow::printText(std::string mytext, int x, int y)
{
	printText(mytext, x, y, 24, WHITE, "Montserrat-Regular.ttf");
}

void DisplayWindow::printText(std::string mytext, int x, int y, int size)
{
	printText(mytext, x, y, size, WHITE, "Montserrat-Regular.ttf");
}

void DisplayWindow::printText(std::string mytext, int x, int y, int size, sf::Color color)
{
	printText(mytext, x, y, size, color, "Montserrat-Regular.ttf");
}

void DisplayWindow::printText(std::string mytext, int x, int y, int size, sf::Color font_size, std::string font_name)
{
	// declare font object and load from from disk
	sf::Font font;
	std::string font_to_load = "GUI/" + font_name;
	if (!font.loadFromFile(font_to_load)) { std::cout << "Error loading font." << std::endl; return; }
	// init text object and set params
	sf::Text text;
	text.setFont(font);
	text.setString(mytext);
	text.setCharacterSize(size); // in pixels, not points!
	text.setColor(font_size);
	text.setPosition({ float(x), float(y) });

	// draw the text
	window->draw(text);
}

void DisplayWindow::drawGraph()
{
	sf::RectangleShape bg;
	bg.setSize({ 800, 500 });
	bg.setFillColor(sf::Color(37, 41, 44));
	bg.setOutlineColor(sf::Color(54, 59, 63));
	bg.setOutlineThickness(10.f);
	bg.setPosition({ 455, 195 });
	window->draw(bg);
	for (int i = 1; i <= 41; i++)
	{
		sf::RectangleShape line;
		line.setSize({ 800, 1 });
		line.setFillColor(sf::Color(54, 59, 63));
		line.setPosition({ 455.f, float(195 + 500 / 40 * i) });
		window->draw(line);
		std::string print = std::to_string(31 - i);
		printText(print, 420, (195 + 500 / 40 * i) - 500 / 40 + 4, 13, WHITE);
	}


}

void DisplayWindow::updateTH(int temp, int humid)
{
	this->temp = temp;
	this->humid = humid;
}

DisplayWindow::~DisplayWindow()
{
	delete window;
}
