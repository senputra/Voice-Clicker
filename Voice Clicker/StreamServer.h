#pragma once

#ifndef STREAM_SERVER_H
#define STREAM_SERVER_H
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "Buffer.h"
#include <iostream>

using boost::asio::ip::udp;

class StreamServer
{
public:
	StreamServer(boost::asio::io_context& io_context, Buffer* buffer,int port)
		: socket_(io_context, udp::endpoint(udp::v4(), port))
	{
		buffer_ = buffer;
		start_receive();
	}

private:
	void start_receive()
	{
		socket_.async_receive_from(
			boost::asio::buffer(reinterpret_cast<char*>(buffer_->getWriterPointer()),384), remote_endpoint_,
			boost::bind(&StreamServer::handle_receive, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

	void handle_receive(const boost::system::error_code& error,
		std::size_t /*bytes_transferred*/)
	{
		if (!error)
		{
			start_receive();
		}
	}

	void handle_send(boost::shared_ptr<std::string> /*message*/,
		const boost::system::error_code& /*error*/,
		std::size_t /*bytes_transferred*/)
	{
	}

	udp::socket socket_;
	udp::endpoint remote_endpoint_;
	Buffer *buffer_;
};

#endif
