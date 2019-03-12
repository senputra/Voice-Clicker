// Voice Clicker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Buffer.h"
#include "StreamServer.h"
#include "InputEngineServer.h"
#include "InputEngine.h"
#include "PlaybackEngine.h"
#include "mDNS/mDNS.h"
#include <iostream>
#include <thread>
#include <string>

Poco::DNSSD::ServiceHandle inputServerHandle;
Poco::DNSSD::ServiceHandle audioServerHandle;
mDNS * mmDNS;

int AUDIO_PORT = 0;
int INPUT_PORT = 0;

std::string AUDIO_PORT_KEY = "vc_audio";
std::string	INPUT_PORT_KEY = "vc_input";

void advertise() {
	if (AUDIO_PORT != 0 && INPUT_PORT != 0) {
		mmDNS->addProps(AUDIO_PORT_KEY, std::to_string(AUDIO_PORT));
		mmDNS->addProps(INPUT_PORT_KEY, std::to_string(INPUT_PORT));
		inputServerHandle = mmDNS->advertise("_vcHello._udp", 15643);
		printf("\nAdvertised %d %d", INPUT_PORT, AUDIO_PORT);
	}
}

void startAudio(Buffer *buffer_) {
	PlaybackEngine *engine_ = new PlaybackEngine(buffer_);
}

void startNetwork(Buffer *buffer_, int port) {
	try {
		boost::asio::io_context io_context;
		StreamServer server(io_context, buffer_, port);
		AUDIO_PORT = server.getLocalPort();
		advertise();
		//int audioServerPort = server.getLocalPort();

		/*if (mmDNS != nullptr) {
			audioServerHandle = mmDNS->advertise("_VCAudio._udp", audioServerPort);
		}*/


		printf("\nAudio Stream server is up at port: %d\n", AUDIO_PORT);
		io_context.run();
		std::cin.get();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

}

void startInputEngine(int port) {
	InputEngine *ieEngine = new InputEngine();
	boost::asio::io_context io_context;
	InputEngineServer *server = new InputEngineServer(io_context, ieEngine, port);
	INPUT_PORT = server->getLocalPort();
	advertise();
	/*int inputServerPort = server->getLocalPort();

	if (mmDNS != nullptr) {
		inputServerHandle = mmDNS->advertise("_VCInput._udp", inputServerPort);
	}*/

	printf("\nKeyboard and trackpad servers are up at port: %d\n", INPUT_PORT);
	io_context.run();
	std::cin.get();
}

void startStreamEngine(int port) {
	Buffer *buffer_ = new Buffer();
	std::thread networkThread(startNetwork, buffer_, port);
	std::thread audioThread(startAudio, buffer_);
	std::cin.get();
}


int main()
{
	std::cout << "Welcome to Voice Clicker\n";
	mmDNS = new mDNS();
	Buffer *buffer_ = new Buffer();
	std::thread streamEngineThread(startStreamEngine, 0);
	std::thread inputEngineThread(startInputEngine, 0);

	
	std::cout << "mDNS started.\n";
	std::cin.get(); 
	
	mmDNS->discardAdvertise(inputServerHandle);
	mmDNS->discardAdvertise(audioServerHandle);

	delete(mmDNS);
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
