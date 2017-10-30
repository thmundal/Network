#pragma comment(lib, "sfml-network.lib");
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>

#include <iostream>

int main()
{

	sf::TcpSocket socket;
	socket.connect("192.168.1.43", 23);


	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	char buffer[256];
	std::size_t received = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		socket.receive(buffer, sizeof(buffer), received);
		std::cout << "server said " << buffer << std::endl;

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}