#pragma once
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/error.hpp>
#include <string>

using namespace boost::asio;

class ClientConnection : public boost::enable_shared_from_this<ClientConnection> {
public:
	static const size_t maxBufferSize = 512;
private:
	ip::tcp::socket socket_;
	std::array<char, maxBufferSize> message_;
	std::string login;
public:
	ClientConnection(const any_io_executor& context);
	ip::tcp::socket& get_socket();
	void async_handle();

private:
	void on_read(const boost::system::error_code& err, size_t bytes);
	void on_write(const boost::system::error_code& err, size_t bytes);
};