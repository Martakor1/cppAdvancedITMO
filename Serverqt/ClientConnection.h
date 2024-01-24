#pragma once
#include <boost/asio.hpp>
#include <boost/asio/error.hpp>
#include <string>
#include "ChatMessage.h"
#include "ServerCommand.h"
#include "User.h"

class ChatServer;

class ClientConnection : public std::enable_shared_from_this<ClientConnection> {
public:
	static const size_t maxBufferSize = 1024;
private:
	boost::asio::ip::tcp::socket socket_;
	std::array<char, maxBufferSize> message_;
	QUuid clientId;
	ChatServer *serv;
	bool loggedIn = false;
public:
	ClientConnection(const boost::asio::any_io_executor& context, ChatServer *serv);
	~ClientConnection();
	boost::asio::ip::tcp::socket& get_socket();
	void async_handle();
	void receiveMessage(std::shared_ptr<ChatMessage> msg);
	void sendMessage(ServerCommand::CrudType type, std::shared_ptr<ChatMessage> msg);
	void sendLogin(ServerCommand::CrudType type, std::shared_ptr<User> usr);
	void checkLogin(std::shared_ptr<User> usr);
	const QUuid& getClientId();

private:
	void sendBytesWithSize(const QByteArray& array);
	void on_read(const boost::system::error_code& err, size_t bytes);
	void on_write(const boost::system::error_code& err, size_t bytes);
};