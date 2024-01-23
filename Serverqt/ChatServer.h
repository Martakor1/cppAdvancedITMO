#pragma once
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "ClientConnection.h"
#include "ChatRoom.h"



class ChatServer : public boost::enable_shared_from_this<ChatServer> {
	//либо сделать connection вложенным классом либо объединить в один?
	//скорее вложенным. Server получает запросы и направляет на них коннекшены
private:
	boost::asio::ip::tcp::acceptor acceptor_;
	ChatRoom uniqueChatRoom; //сейчас chatServer выполняет роль и контейнера всей информации. Возможно вынесение в отдельный msgService
public:
	ChatServer(io_context& context, const boost::asio::ip::tcp::endpoint& endpoint);
	void start_listen();
	ChatRoom& getChatRoom(const QUuid& chatId);
private:
	void on_accept(std::shared_ptr<ClientConnection> newConnection, const boost::system::error_code& err);
};