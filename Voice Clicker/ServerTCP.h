#pragma once

#ifndef SERVERTCP_H
#define SERVERTCP_H
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "Buffer.h"
#include <iostream>	

using boost::asio::ip::tcp;

class tcp_connection
	: public boost::enable_shared_from_this<tcp_connection>{
public:
	typedef boost::shared_ptr<tcp_connection> pointer;

	static pointer create(boost::asio::io_context& io_context){
		return pointer(new tcp_connection(io_context));
	}

	tcp::socket& socket(){
		return socket_;
	}

	void accept(Buffer *buffer){
		socket_.async_read_some(boost::asio::buffer(buffer->getlistenerPointer(),
			buffer->getMaxSizeInBytes()), 
			boost::bind(&tcp_connection::readHandler,
				shared_from_this()));
		
	}

	void readHandler() {
		return;
	}

private:
	tcp_connection(boost::asio::io_context& io_context)
		: socket_(io_context){

	}

	tcp::socket socket_;
	std::string message_;
};




class ServerTCP
{
public:
	ServerTCP(boost::asio::io_context& io_context, Buffer* buffer, int port)
		: acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
	{
		buffer_ = buffer;
		start_accept();
	}

private:
	Buffer *buffer_;
	void start_accept()
	{
		tcp_connection::pointer new_connection =
			tcp_connection::create(acceptor_.get_executor().context());
		
		
		acceptor_.async_accept(new_connection->socket(),
			boost::bind(&ServerTCP::handle_accept, this, 
				new_connection,
				boost::asio::placeholders::error));
	}

	void handle_accept(tcp_connection::pointer new_connection,
		const boost::system::error_code& error)
	{
		if (!error)
		{
			//MY CODE HERE
			new_connection->accept(buffer_);
		}

		start_accept();
	}

	tcp::acceptor acceptor_;
};

#endif
