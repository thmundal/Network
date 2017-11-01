#pragma comment(lib, "sfml-network.lib");
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include "DisplayWindow.h"
#include <string>
#include <iostream>

std::string recieve(char buffer[256]);

int main()
{
	sf::Socket::Status client_status;
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("192.168.1.43", 23);

	socket.setBlocking(false);

	if (status != 0) {
		std::cout << "Could not connect to server";
		return 0;
	}

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

		client_status = socket.receive(buffer, sizeof(buffer), received);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && client_status == 0) {
			recieve(buffer);
		}
	}

	return 0;
}

std::string recieve(char buffer[256])
{
	//std::cout << "server said " << buffer << std::endl;

	int i = 0;
	bool write = false;
	std::string return_string;

	for (int i = 0; i < 256; i++)
	{
		if (buffer[i] == '{') {
			write = true;
			continue;
		}

		if (buffer[i] == '}') {
			write = false;
			break;
		}

		if (write) {
			return_string += buffer[i];
		}
	}
	std::cout << return_string << std::endl;
	return return_string;
}