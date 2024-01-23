#include "ClientConnection.h"
#include <boost/bind.hpp>
#include <iostream>

using namespace boost::asio;

ClientConnection::ClientConnection(const any_io_executor& context) :
	socket_(context), message_()
{
}

ip::tcp::socket& ClientConnection::get_socket() {
	return socket_;
}

void ClientConnection::async_handle() {
	std::cout << "accepted" << std::endl;
	socket_.async_read_some(buffer(message_), boost::bind(&ClientConnection::on_read, shared_from_this(), _1, _2));
}


void ClientConnection::on_read(const boost::system::error_code& err, size_t bytes) {
	if (!err) {
		size_t size = *(size_t*)message_.data();
		//if (bytes != size + 4) return; //пока так

		std::cout << "red, thread id " << std::this_thread::get_id() << std::endl;
		std::cout << "message is '" << message_.data() + 4 << "'" << " size " << bytes << std::endl;
		socket_.async_write_some(buffer(message_, bytes), boost::bind(&ClientConnection::on_write, shared_from_this(), _1, _2));
	}
	else {
		std::cout << err.message() << std::endl;
		//сокет сам уничтожится и закроется, если не будет shared_ptr на this
	}
}

void ClientConnection::on_write(const boost::system::error_code& err, size_t bytes) {
	if (!err) {
		std::cout << "wrote, thread id!" << std::this_thread::get_id() << std::endl;
		socket_.async_read_some(buffer(message_), boost::bind(&ClientConnection::on_read, shared_from_this(), _1, _2));
	}
	else {
		std::cout << err.message() << std::endl;
	}
}