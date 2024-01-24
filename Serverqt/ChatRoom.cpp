#include "ChatRoom.h"

class ServerCommand;

ChatRoom::ChatRoom(): msgs(), clients() {}

void ChatRoom::connectClient(std::shared_ptr<ClientConnection> client) {
	clients.insert(client);
	for (const auto& msg : msgs) {
		client->sendMessage(ServerCommand::CrudType::create, msg);
	}
}

void ChatRoom::disconnectClient(std::shared_ptr<ClientConnection> client) {
	clients.erase(client);
}

void ChatRoom::addMessage(std::shared_ptr<ChatMessage> msg) {
	msg->setStatus(true);
	msgs.push_back(msg);
	for (const std::shared_ptr<ClientConnection>& client: clients)
	{
		if (client->getClientId() == msg->getSenderId())
			client->sendMessage(ServerCommand::CrudType::update, msg);
		else {
			client->sendMessage(ServerCommand::CrudType::create, msg);
		}
	}
}
