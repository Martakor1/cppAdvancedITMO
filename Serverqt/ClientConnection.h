#pragma once
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/error.hpp>
#include <string>
#include "ChatMessage.h"
#include "ChatServer.h"

using namespace boost::asio;

class ClientConnection : public boost::enable_shared_from_this<ClientConnection> {
public:
	static const size_t maxBufferSize = 512;
private:
	boost::asio::ip::tcp::socket socket_;
	std::array<char, maxBufferSize> message_;
	QUuid cliendId;
	ChatServer *server;
public:
	ClientConnection(const any_io_executor& context, ChatServer *serv);
	ip::tcp::socket& get_socket();
	void async_handle();
	void receiveMessage(std::shared_ptr<ChatMessage> msg);
	void sendMessage(std::shared_ptr<ChatMessage> msg);
	const QUuid& getClientId();

private:
	void sendBytesWithSize(const QByteArray& array);
	void on_read(const boost::system::error_code& err, size_t bytes);
	void on_write(const boost::system::error_code& err, size_t bytes);
};