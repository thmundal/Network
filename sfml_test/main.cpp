#pragma comment(lib, "sfml-network.lib")

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include "DisplayWindow.h"
#include <string>
#include <iostream>
#include "CSVWriter.h"

std::string recieve(char buffer[256]);

int main()
{
	DisplayWindow context(200, 200, "Hello, world!");

	sf::Socket::Status client_status;
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("192.168.1.43", 23);


	if (status != sf::Socket::Status::Done) {
		std::cout << "Could not connect to server" << std::endl;
		return 0;
	}
	else {
		std::cout << "Connected to arduino" << std::endl;
	}

	//socket.setBlocking(false);

	char buffer[256];
	std::size_t received = 0;
	
	/*CSVWriter writer("Data.csv");
	std::set<int> dataList_2 = { x, y };
	writer.addDatainRow(dataList_2.begin(), dataList_2.end());
	*/
	bool request = false;
	bool waiting = false;

	context.update([&request, &received, &waiting, &client_status, &socket, &buffer](double delta_time) {

		request = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

		// Simulate keypress:
		//if (!request)
		//	request = true;

		if (request && !waiting) {
			std::cout << "Request data from arduino..." << std::endl;
			client_status = socket.receive(buffer, sizeof(buffer), received);
			waiting = true;
		}

		if (waiting && client_status == socket.Done) {
			std::cout << "Data received, handle..." << std::endl;
			recieve(buffer);
			request = false;
			waiting = false;
		}
	});

	context.loop();

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