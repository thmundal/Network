// DHT
#include <dht.h>
dht DHT;
#define DHT11_PIN A0
// /DHT

#include <SPI.h>
#include <UIPEthernet.h>

byte mac[] = {
	0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 43);
IPAddress myDns(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);


// telnet defaults to port 23
EthernetServer server(23);
boolean alreadyConnected = false; // whether or not the client was connected previously

void setup() {
	// initialize the ethernet device
	Ethernet.begin(mac, ip, myDns, gateway, subnet);
	// start listening for clients
	server.begin();
	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}


	Serial.print("Chat server address:");
	Serial.println(Ethernet.localIP());
}

void loop() {
	// wait for a new client:
	EthernetClient client = server.available();

	// when the client sends the first byte, say hello:
	if (client) {
		if (!alreadyConnected) {
			// clear out the input buffer:
			client.flush();
			Serial.println("We have a new client");
			alreadyConnected = true;
		}

		if (client.available() > 0) {
			int chk = DHT.read11(DHT11_PIN);
			String data = "{" + String(DHT.temperature) + "," + String(DHT.humidity) + "}";
			server.print(data);
			delay(1000);
		}
	}
}