#pragma once

#ifndef INPUT_ENGINE_SERVER_H
#define INPUT_ENGINE_SERVER_H
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "InputEngine.h"
#include <iostream>

using boost::asio::ip::udp;

class InputEngineServer
{
public:
	InputEngineServer(boost::asio::io_context& io_context, InputEngine* ieEngine, int port)
		: socket_(io_context, udp::endpoint(udp::v4(), port))
	{
		this->ieEngine = ieEngine;
		start_receive();
	}

private:
	void start_receive()
	{
		socket_.async_receive_from(
			boost::asio::buffer(ieEngine->getCommandBuffer(), 8), remote_endpoint_,
			boost::bind(&InputEngineServer::handle_receive, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

	void handle_receive(const boost::system::error_code& error,
		std::size_t /*bytes_transferred*/)
	{
		//std::cout << "received commmand" << std::endl;
		if (!error)
		{
			ieEngine->execute();
			start_receive();
		}
	}

	udp::socket socket_;
	udp::endpoint remote_endpoint_;
	InputEngine *ieEngine = nullptr;
};

#endif