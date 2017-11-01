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

	DisplayWindow(200, 200, "Hello, world!");

	sf::TcpSocket socket;
	socket.connect("192.168.1.43", 23);
	std::cout << "Connection attempt finished";

	char buffer[256];
	std::size_t received = 0;

	socket.receive(buffer, sizeof(buffer), received);
	recieve(buffer);

	while (true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
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