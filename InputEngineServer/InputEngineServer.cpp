// InputEngineServer.cpp : Defines the exported functions for the DLL application.
//
#include "InputEngineServer.h"

InputEngineServer::InputEngineServer(boost::asio::io_context& io_context, InputEngine* ieEngine, int port)
	: socket_(io_context, udp::endpoint(udp::v4(), port)) {
	this->ieEngine = ieEngine;
	start_receive();
};
void InputEngineServer::start_receive()
{
	socket_.async_receive_from(
		boost::asio::buffer(ieEngine->getCommandBuffer(), 8), remote_endpoint_,
		boost::bind(&InputEngineServer::handle_receive, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void InputEngineServer::handle_receive(const boost::system::error_code& error,
	std::size_t /*bytes_transferred*/)
{
	//std::cout << "received commmand" << std::endl;
	if (!error)
	{
		ieEngine->execute();
		start_receive();
	}
}
