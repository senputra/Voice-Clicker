#pragma once

#ifdef STREAMSERVER_EXPORTS
#define STREAMSERVER_API __declspec(dllexport)
#else
#define STREAMSERVER_API __declspec(dllimport)
#endif // STREAMSERVER_EXPORTS


#ifndef STREAM_SERVER_H
#define STREAM_SERVER_H
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "Buffer.h"
#include <iostream>
#include <stdint.h>


using boost::asio::ip::udp;

class STREAMSERVER_API StreamServer
{
public:
	StreamServer(boost::asio::io_context& io_context, Buffer* buffer, int port);
	~StreamServer();

private:
	void start_receive();

	void handle_receive(const boost::system::error_code& error,
		std::size_t /*bytes_transferred*/);

	void handle_send(boost::shared_ptr<std::string> /*message*/,
		const boost::system::error_code& /*error*/,
		std::size_t /*bytes_transferred*/);

	udp::socket socket_;
	udp::endpoint remote_endpoint_;
	Buffer *buffer_;
};

#endif
