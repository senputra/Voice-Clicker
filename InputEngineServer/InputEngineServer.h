#pragma once

#ifndef INPUT_ENGINE_SERVER_H
#define INPUT_ENGINE_SERVER_H

#ifdef INPUTENGINESERVER_EXPORTS
#define INPUTENGINESERVER_API __declspec(dllexport)
#else 
#define INPUTENGINESERVER_API __declspec(dllimport)
#endif // INTPUTENGINESERVER_EXPORTS


#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "InputEngine.h"
#include <stdint.h>


using boost::asio::ip::udp;

class INPUTENGINESERVER_API InputEngineServer
{
public:
	InputEngineServer(boost::asio::io_context& io_context, InputEngine* ieEngine, int port);
	int getLocalPort();

private:
	void start_receive();

	void handle_receive(const boost::system::error_code& error,
		std::size_t /*bytes_transferred*/);

	udp::socket socket_;
	udp::endpoint remote_endpoint_;
	InputEngine *ieEngine = nullptr;
};

#endif