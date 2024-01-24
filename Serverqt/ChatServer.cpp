#include <SDKDDKVer.h>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <memory>
#include <boost/bind.hpp>
#include <boost/asio/error.hpp>
#include "ChatServer.h"
#include "ClientConnection.h"

using namespace boost::asio;

ChatServer::ChatServer(io_context& context, const ip::tcp::endpoint& endpoint) : acceptor_(context, endpoint), uniqueChatRoom() {

}
	
void ChatServer::start_listen() {
	std::shared_ptr<ClientConnection> newConnection(new ClientConnection(acceptor_.get_executor(), this));
	acceptor_.async_accept(newConnection->get_socket(), boost::bind(&ChatServer::on_accept, shared_from_this(), newConnection, _1));
}


void ChatServer::on_accept(std::shared_ptr<ClientConnection> newConnection, const boost::system::error_code& err) {
	if (!err) {
		newConnection->async_handle();
	}
	else {
		std::cout << err.message() << std::endl;
	}
	start_listen();
}

ChatRoom& ChatServer::getChatRoom(const QUuid& chatId) {
	return uniqueChatRoom; //TODO find by id
}

PasswordService& ChatServer::getPasswordService() {
	return pswdService;
}
