#pragma comment(lib, "sfml-network.lib")

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include "DisplayWindow.h"
#include <string>
#include <iostream>
#include "CSVWriter.h"

std::vector<std::string> recieve(char buffer[256]);
CSVWriter writer = CSVWriter("Data.csv");

int main()
{
	DisplayWindow context(1280, 720, "Temperature and humidity");

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

	socket.setBlocking(false);

	char buffer[256];
	std::size_t received = 0;

	bool request = false;
	bool waiting = false;

	context.update([&request, &received, &waiting, &client_status, &socket, &buffer, &context, &status](double delta_time) {
		request = context.connect;
		
		//std::cout << "request:" << request << " waiting:" << waiting << std::endl;

		if (request && !waiting) {
			client_status = socket.receive(buffer, sizeof(buffer), received);
			std::cout << "Request data from arduino..." << std::endl;
			waiting = true;
		}

		if (waiting && client_status != socket.Done) {
			context.printText("Waiting for data...", 25, 325, 36, sf::Color(225, 77, 67), "SairaSemiCondensed-Regular.ttf");
		}

		if (waiting && client_status == socket.Done) {
			std::cout << "Data received, handle..." << std::endl;
			context.printText("Reading data...", 25, 325, 36, sf::Color(225, 77, 67), "SairaSemiCondensed-Regular.ttf");
			std::vector<std::string> values = recieve(buffer);
			context.updateTH(std::stoi(values.at(0)), std::stoi(values.at(1)));
			request = false;
			waiting = false;
			context.connect = false;
		}

		context.printText("Connection status: " + std::to_string(status), 25, 30, 36, sf::Color(225, 77, 67), "SairaSemiCondensed-Regular.ttf");
		context.printText("Network status: " + std::to_string(client_status) , 25, 75, 36, sf::Color(225, 77, 67), "SairaSemiCondensed-Regular.ttf");
		context.button();
		
		context.drawGraph();
		context.printText("Temperature: " + std::to_string(context.temp) + "C", 25, 180, 36, sf::Color(225, 77, 67), "SairaSemiCondensed-Regular.ttf");
		context.printText("Humidity: " + std::to_string(context.humid) + "%", 25, 275, 36, sf::Color(105, 168, 187), "SairaSemiCondensed-Regular.ttf");
	});

	context.loop();

	socket.disconnect();
	return 0;
}

std::vector<std::string> recieve(char buffer[256])
{
	//std::cout << "server said " << buffer << std::endl;

	int i = 0;
	bool write = false;
	std::string return_string;
	std::vector<std::string> values{ "0", "0" };
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

	writer.addDatainRow(values);
	std::cout << values.at(0) << ", " << values.at(1) << std::endl;
	return values;
}