#include "ClientConnection.h"
#include <boost/bind.hpp>
#include <iostream>
#include <QByteArray>
#include "ServerCommand.h"
#include "CommandParseException.cpp"
#include "ChatServer.h"
#include <QIODevice>

using namespace boost::asio;

ClientConnection::ClientConnection(const any_io_executor& context, ChatServer *serv) :
	socket_(context), message_(), serv(serv)
{
}

ip::tcp::socket& ClientConnection::get_socket() {
	return socket_;
}

void ClientConnection::async_handle() {
	std::cout << "accepted" << std::endl;
	socket_.async_read_some(buffer(message_), boost::bind(&ClientConnection::on_read, shared_from_this(), _1, _2));
}


void ClientConnection::receiveMessage(std::shared_ptr<ChatMessage> msg) {
	clientId = msg->getSenderId();
	serv->getChatRoom(msg->getChatId()).addMessage(msg);
}


void ClientConnection::sendMessage(ServerCommand::CrudType type, std::shared_ptr<ChatMessage> msg) {
	ServerCommand sendCommand(this, ServerCommand::Domain::msg, type, msg);
	sendBytesWithSize(sendCommand.toBytes());
}


void ClientConnection::on_read(const boost::system::error_code& err, size_t bytes) {
	if (!err) {
		QDataStream st(QByteArray(message_.data(), bytes));
		st.startTransaction();
		QByteArray jsonData;
		for (;;) {
			st.startTransaction();
			st >> jsonData;
			if (st.commitTransaction()) {
				try {
					auto c = ServerCommand(this, jsonData);
					c.exec();
				}
				catch (CommandParseException& e) {
					//некорректный json от клиента. Игнорируем...
					std::cout << e.what() << std::endl;
				}
			}
			else {
				break;
			}
		}
	}
	else {
		std::cout << err.message() << std::endl;
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

const QUuid& ClientConnection::getClientId() {
	return clientId;
}

void ClientConnection::sendBytesWithSize(const QByteArray& array) {
	QByteArray buf;
	QDataStream st(&buf, QIODevice::WriteOnly);
	st << array;
	socket_.async_write_some(buffer(buf.constData(), buf.size()), boost::bind(&ClientConnection::on_write, shared_from_this(), _1, _2));
}