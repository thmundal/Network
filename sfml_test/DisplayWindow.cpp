#include "DisplayWindow.h"

#define WHITE sf::Color::White
#define BLACK sf::Color::Black
#define GREY sf::Color::Grey
#define RED sf::Color::Red
#define GREEN sf::Color::Green
#define BLUE sf::Color::Blue

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
		window->clear(sf::Color::White);
		printText("Hello", 100, 200, 24, RED, "Montserrat-Regular.ttf");
		printText("World", 200, 300, 36, BLUE, "SairaSemiCondensed-Regular.ttf");
		window->display();
	}
}

void DisplayWindow::printText(char mytext[], int x, int y)
{
	// declare font object and load from from disk
	sf::Font font;
	if (!font.loadFromFile("GUI/SairaSemiCondensed-Regular.ttf")) { std::cout << "Error loading font." << std::endl; return; }
	// init text object and set params
	sf::Text text;
	text.setFont(font);
	text.setString(mytext);
	text.setCharacterSize(24); // in pixels, not points!
	text.setColor(sf::Color::Black);
	text.setPosition({ float(x), float(y) });

	// draw the text
	window->draw(text);
}

void DisplayWindow::printText(char mytext[], int x, int y, int size, sf::Color font_size, std::string font_name)
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

DisplayWindow::~DisplayWindow()
{
	delete window;
}
