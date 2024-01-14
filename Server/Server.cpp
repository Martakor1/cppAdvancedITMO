// Server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <SDKDDKVer.h>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <memory>
#include <boost/bind.hpp>
#include <boost/asio/error.hpp>

using namespace boost::asio;


class EchoConnection: public boost::enable_shared_from_this<EchoConnection> {
private:
	ip::tcp::socket socket_;
	std::array<char, 128> message_;
public:
	EchoConnection(const any_io_executor& context) : socket_(context), message_() {
	}

	ip::tcp::socket& get_socket() {
		return socket_;
	}

	void async_handle() {
		std::cout << "accepted" << std::endl;
		socket_.async_read_some(buffer(message_), boost::bind(&EchoConnection::on_read, shared_from_this(), _1, _2));
	}

private:
	void on_read(const boost::system::error_code& err, size_t bytes) {
		if (!err) {
			std::cout << "red, thread id " << std::this_thread::get_id() << std::endl;
			std::cout << "message is '" << message_.data() << "'" << std::endl;
			socket_.async_write_some(buffer(message_, bytes), boost::bind(&EchoConnection::on_write, shared_from_this(), _1, _2));
		}
		else {
			std::cout << err.message() << std::endl;
			//сокет сам уничтожится и закроется, если не будет shared_ptr на this
		}
	}

	void on_write(const boost::system::error_code& err, size_t bytes) {
		if (!err) {
			std::cout << "wrote, thread id!" << std::this_thread::get_id() << std::endl;
			socket_.async_read_some(buffer(message_), boost::bind(&EchoConnection::on_read, shared_from_this(), _1, _2));
		}
		else {
			std::cout << err.message() << std::endl;
		}
	}
};


class EchoServer: public boost::enable_shared_from_this<EchoServer> {
//либо сделать connection вложенным классом либо объединить в один?
//скорее вложенным. Server получает запросы и направляет на них коннекшены
private:
	ip::tcp::acceptor acceptor_;
public:
	EchoServer(io_context& context, const ip::tcp::endpoint& endpoint) : acceptor_(context, endpoint) {
		
	}
	
	void start_listen() {
		boost::shared_ptr<EchoConnection> newConnection(new EchoConnection(acceptor_.get_executor()));
		acceptor_.async_accept(newConnection->get_socket(), boost::bind(&EchoServer::on_accept, shared_from_this(), newConnection, _1));
	}
private:
	void on_accept(boost::shared_ptr<EchoConnection> newConnection, const boost::system::error_code& err) {
		if (!err) {
			newConnection->async_handle();
		}
		else {
			std::cout << err.message() << std::endl;
		}
		start_listen();
	}
};
//void on_read(const boost::system::error_code&, size_t s) {
//	std::cout << "on_read " << s << std::endl;
//}
//
//size_t customCompletion(const boost::system::error_code&, size_t bytes) {
//	std::cout << "completion function work " << bytes << std::endl;
//	return 100;
//}

//void on_accept(const boost::system::error_code& err) {
//	std::cout << "accepted" << std::endl;
//}
//
//void handle_clients() {
//	
//}

