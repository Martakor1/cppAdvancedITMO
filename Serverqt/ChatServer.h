#pragma once
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "ChatRoom.h"
#include "PasswordService.h"

class ClientConnection;

class ChatServer : public boost::enable_shared_from_this<ChatServer> {
private:
	boost::asio::ip::tcp::acceptor acceptor_;
	ChatRoom uniqueChatRoom; //сейчас chatServer выполняет роль и контейнера всей информации. Возможно вынесение в отдельный msgService
	PasswordService pswdService;
public:
	ChatServer(boost::asio::io_context& context, const boost::asio::ip::tcp::endpoint& endpoint);
	void start_listen();
	ChatRoom& getChatRoom(const QUuid& chatId);
	PasswordService& getPasswordService();
private:
	void on_accept(std::shared_ptr<ClientConnection> newConnection, const boost::system::error_code& err);
};