#pragma comment(lib, "sfml-network.lib")

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include "DisplayWindow.h"
#include <string>
#include <iostream>
#include "CSVWriter.h"

std::string recieve(char buffer[256]);
CSVWriter writer = CSVWriter("Data.csv");

int main()
{



	DisplayWindow context(1280, 720, "Hello, world!");
	sf::Socket::Status client_status;
	sf::TcpSocket socket;
	//sf::Socket::Status status = socket.connect("192.168.1.43", 23);
	sf::Socket::Status status = socket.connect("79.160.104.89", 2323); // Thomas sin Arduino


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
	std::vector<std::string> values{ "", "" };
	int val = 0;

	for (int i = 0; i < 256; i++)
	{
		if (buffer[i] == '{') {
			write = true;
			continue;
		}

		if (buffer[i] == ',') {
			val = 1;
			i++;
		}

		if (buffer[i] == '}') {
			val = 0;
			write = false;
			break;
		}

		if (write) {
			values[val] += buffer[i];
			return_string += buffer[i];
		}
	}

	std::set<int> dataList_2 = { 1, 2 };
	writer.addDatainRow(values.begin(), values.end());
	std::cout << return_string << std::endl;
	return return_string;
}