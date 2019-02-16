// Voice Clicker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "StreamServer.h"
#include "InputEngineServer.h"
#include "InputEngine.h"
#include "PlaybackEngine.h"
#include "Buffer.h"
#include <iostream>
#include <thread>

void startAudio(Buffer *buffer_) {
	PlaybackEngine *engine_ = new PlaybackEngine(buffer_);
}

void startNetwork( Buffer *buffer_, int port) {
	try{
		boost::asio::io_context io_context;
		StreamServer server(io_context, buffer_, port);
		io_context.run();
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
	io_context.run();
	std::cout << "\n Keyboard and trackpad servers are up.\n";
	std::cin.get();
}

void startStreamEngine(int port) {
	Buffer *buffer_ = new Buffer();
	std::thread networkThread(startNetwork, buffer_, port);
	std::thread audioThread(startAudio, buffer_);
	std::cout << "\n Audio Stream server is up.\n";
	std::cin.get();
}

int main()
{
	std::cout << "Welcome to Voice Clicker\n";
	Buffer *buffer_ = new Buffer();
	std::thread streamEngineThread(startStreamEngine, 5008);
	std::thread inputEngineThread(startInputEngine, 5009);

	std::cout << "main function done" << std::endl;
	
	char input;
	std::cout << "\nPlaying ... press <enter> to quit.\n";
	std::cin.get(input);


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
